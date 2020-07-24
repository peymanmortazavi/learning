#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/fcntl.h>
#include <string.h>
#include <errno.h>

#include "utils.h"


int create_barrier(char* request_fifo_name, char* name, int size) {
  // Open the request fifo file to write the request.
  int request_fd = -1;
  if ((request_fd = open(request_fifo_name, O_WRONLY)) == -1) {
    fprintf(stderr, "Cannot open request fifo file '%s': %s\n", request_fifo_name, strerror(errno));
    return -1;
  }
  // Now write the request.
  ssize_t bytecount;
  size_t len = strlen(name) + 2;
  char* request = malloc(len * sizeof(char));
  strcpy(request + 1, name);
  request[0] = size;
  request[len-1] = '\n';
  fprintf(stderr, "len: %ld - ('%s') %d@\n", len, request, request_fd);
  if ((bytecount = write(request_fd, request, len)) == -1) {
    fprintf(stderr, "Could not write to request fifo %s: %s\n", request_fifo_name, strerror(errno));
    return -1;
  }
  close(request_fd);
  free(request);
  return 0;
}


int wait_barrier(char* name) {
  // Now open the release file.
  char* release_barrier = get_release_barrier(name);
  fprintf(stdout, "Opening release fifo %s to read one character from.\n", release_barrier);
  int release_fd;
  if ((release_fd = open(release_barrier, O_RDONLY)) == -1) {
    fprintf(stderr, "Could not read from file %s : %s\n", release_barrier, strerror(errno));
    return -1;
  }
  char buffer;
  ssize_t bytecount;
  if ((bytecount = read(release_fd, &buffer, 1)) != 1) {
    fprintf(stderr, "Could not read from the release %s\n", release_barrier);
    return -1;
  }
  return 0;
}


int main(int argc, char* argv[]) {
  if (create_barrier("test.request", "a", 3) != 0) {
    fprintf(stderr, "Could not create barrier bar1\n");
    return 1;
  }
  // if (create_barrier("test.request", "bar3", 4) != 0) {
    // fprintf(stderr, "Could not create barrier bar3\n");
    // return 1;
  // }
  // if (wait_barrier("bar1") != 0) {
    // fprintf(stderr, "fatal error on bar1\n");
    // return 1;
  // }
  // if (wait_barrier("bar2") != 0) {
    // fprintf(stderr, "fatal error on bar2\n");
    // return 1;
  // }
  fprintf(stdout, "This is interesting\n");
  return 0;
}