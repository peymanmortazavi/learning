#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  char* filename = argv[1];
  struct stat file_info;
  if(stat(filename, &file_info) != 0) {
    return -1;
  }
  char* output = malloc(40 * sizeof(char));
  if (strftime(output, 40, "%D %H:%M:%S", localtime(&file_info.st_mtime)) == 0) {
    return -1;
  }
  fprintf(stdout, "%s\n", output);
  return 0;
}
