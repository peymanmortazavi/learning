#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>


int is_executable_file(char* path) {
  struct stat info;
  if (stat(path, &info) == -1) return 0;
  return S_ISREG(info.st_mode) && S_IXOTH & info.st_mode || (S_IXGRP & info.st_mode && info.st_gid == getegid()) || (S_IXUSR & info.st_mode && info.st_uid == geteuid());
}


int contains_slash(const char* path) {
  for(unsigned int index = 0; path[index] != 0; index++) {
    if (path[index] == '/') return 1;
  }
  return 0;
}


char* find_location(char* path) {
  char* path_parts = getenv("PATH");
  size_t cursor = -1;
  char* current_path = malloc(PATH_MAX*sizeof(char));
  for(size_t i = 0;; i++) {
    if(path_parts[i] == 0 || path_parts[i] == ':') {
      if (cursor < 0) {
        cursor = -1;
      }
      else {
        current_path[cursor + 1] = 0;
        strcat(current_path, "/");
        strcat(current_path, path);
        if (is_executable_file(current_path)) {
          return current_path;
        } else {
          cursor = -1;
        }
      }
    } else {
      current_path[++cursor] = path_parts[i];
    }
    if(path_parts[i] == 0) break;
  }
  free(current_path);
  return NULL;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return -1;
  }
  char* path = argv[1];
  if (contains_slash(path)) {
    if (is_executable_file(path)) fprintf(stdout, "%s\n", path);
    return 0;
  }
  char* result;
  if ((result = find_location(path)) != NULL) {
    fprintf(stdout, "%s\n", result);
    return 0;
  }
  return 0;
}
