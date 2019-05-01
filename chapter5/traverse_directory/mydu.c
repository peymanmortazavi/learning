#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/limits.h>

#include "queue.h"


char* join(char* base, char* part) {
  size_t len = strlen(base);
  if (len > PATH_MAX) {
    errno = ENAMETOOLONG;
    return NULL;
  }
  char* new_path = malloc(PATH_MAX * sizeof(char));
  memcpy(new_path, base, len);
  if (new_path[len-1] != '/' && part[0] != '/') strcat(new_path, "/");
  strcat(new_path, part);
  new_path[strlen(new_path)] = 0;
  return new_path;
}


void traverse_level_first(char* path) {
  queue_t q;
  queue_init(&q);
  DIR* dir_info;
  char* base;
  struct dirent* entry;
  enq(&q, path);
  while((base = deq(&q)) != NULL) {
    if ((dir_info = opendir(base)) != NULL) {
      while((entry = readdir(dir_info)) != NULL) {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) continue;
        char* new_path = join(base, entry->d_name);
        enq(&q, new_path);
        fprintf(stdout, "%s\n", new_path);
      }
    }
    closedir(dir_info);
  }
}


void traverse_level(char* path, int level) {
  char* space_line = malloc((level + 1) * sizeof(char));
  for(int i = 0; i < level; i++) space_line[i] = ' ';
  space_line[level] = 0;
  DIR* info;
  struct dirent* entry;
  if((info = opendir(path)) != NULL) {
    while((entry = readdir(info)) != NULL) {
      if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) continue;
      struct stat einfo;
      char id = '?';
      char* url = join(path, entry->d_name);
      if (stat(url, &einfo) == 0) {
        id = S_ISREG(einfo.st_mode) ? 'F' : 'D';
      }
      fprintf(stdout, "%s(%c) %s\n", space_line, id, entry->d_name);
      traverse_level(url, level + 2);
    }
  }
  closedir(info);
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
    return 1;
  }
  if (argc == 3 && strcmp(argv[2], "-b") == 0) {
    traverse_level_first(argv[1]);
  } else {
    traverse_level(argv[1], 0);
  }
	return 0;
}
