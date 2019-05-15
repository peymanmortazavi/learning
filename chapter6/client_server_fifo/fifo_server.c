#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils.h"


int main(int argc, char* argv[]) {
  // create the request fifo if possible.
  if (create_request_fifo("request") != 0 ) {
    fprintf(stderr, "Could not create request fifo: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  char* buffer = malloc(256 * sizeof(char));
  ssize_t bytecount;
  for (;;) {
    // now open the fifo for reading
    int request_fd;
    while((request_fd = open("request", O_RDONLY)) != 0 && errno == EINTR);
    if (request_fd <= 0) {
      fprintf(stderr, "Error opening the request fifo: %s\n", strerror(errno));
      return EXIT_FAILURE;
    }
    // okay now start an infinite loop working on this.
    for (;;) {
      // now start reading from the file. Every time you read.
      while((bytecount = read(request_fd, buffer, 255)) < 0 && errno == EINTR);
      if (bytecount < 0) {
        fprintf(stderr, "Could not read from the request fifo: %s\nexiting now\n.", strerror(errno));
        break;
      } else if (bytecount == 0) {
        fprintf(stdout, "No clients are listening to the fifo, stop read operations.\n");
        break;
      }
      fprintf(stdout, "Received response pipe '%s', going to read from it.\n", buffer);
    }
  }
  return 0;
}