#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"


int main(int argc, char* argv[]) {
  // open the request fifo for writing.
  int request_fifo;
  while ((request_fifo = open("request", O_WRONLY)) <= 0 && errno == EINTR);
  if (request_fifo <= 0) {
    fprintf(stderr, "Coult not open the request fifo for reading: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  // now get the current pid.
  pid_t mypid = getpid();
  char* name = malloc(12 * sizeof(char));
  int name_size = sprintf(name, "%d", mypid);
  fprintf(stdout, "Creating response fifo '%s'\n", name);
  if(create_response_fifo(name) != 0) {
    fprintf(stderr, "Could not create response fifo '%s'\n", name);
    return EXIT_FAILURE;
  }
  // now write this name to the request fifo so the server can learn about this.
  ssize_t bytecount;
  while((bytecount = write(request_fifo, name, name_size)) <= 0 && errno == EINTR);
  if (bytecount <= 0) {
    fprintf(stderr, "Error writing to the request fifo: '%s'\n", strerror(errno));
    unlink(name);
    return EXIT_FAILURE;
  }
  unlink(name);
  return EXIT_SUCCESS;
}