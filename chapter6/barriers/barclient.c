#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils.h"


int waitbarrier(char* name, char wb) {
  char* request_name = get_request_barrier(name);
  int request_fifo;
  if ( (request_fifo = open(request_name, O_WRONLY)) == -1) {
    fprintf(stderr, "Could not open the request fifo.\n");
    free(request_name);
    return -1;
  }
  if (write(request_fifo, &wb, 1) != 1) {
    fprintf(stderr, "Could not write to the fifo.\n");
    free(request_name);
    close(request_fifo);
    return -1;
  }
  free(request_name);
  close(request_fifo);
  // now wait for the response.
  char* release_name = get_release_barrier(name);
  int release_fifo;
  if ( (release_fifo = open(release_name, O_RDONLY)) == -1) {
    fprintf(stderr, "Could not open the release fifo file '%s' for reading.\n", release_name);
    free(release_name);
    return -1;
  }
  char c;
  ssize_t len;
  if ((len = read(release_fifo, &c, 1)) <= 0) {
    if (len == 0) {
      fprintf(stdout, "Received an eof!\n");
      free(release_name);
      close(release_fifo);
      return 0;
    }
    if (len < 0) {
      fprintf(stderr, "Encountered an error while reading from %s\n", release_name);
      free(release_name);
      close(release_fifo);
      return -1;
    }
  }
  fprintf(stdout, "BUFFER: %c\n", c);
  free(release_name);
  close(release_fifo);
	return 0;
}


int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage : %s <name> <number>\n", argv[0]);
    return 1;
  }
  char* name = argv[1];
	fprintf(stdout, "waiting for barrier %s\n", name);
  if (waitbarrier(argv[1], argv[2][0]) != 0) {
    fprintf(stderr, "FATAL: failed wait\n");
    return 1;
  }
  fprintf(stdout, "Released\n");
	return 0;
}
