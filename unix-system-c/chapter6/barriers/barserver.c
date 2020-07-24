#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "utils.h"


int read_until(int fd, void* buffer, int len) {
	int counter = 0;
	while (counter < len) {
		ssize_t byte_count;
		if ( (byte_count = read(fd, buffer + counter, len - counter)) == -1) {
			fprintf(stderr, "bad error: %d %s\n", errno, strerror(errno));
			return byte_count;
		}
		counter += byte_count;
	}
	return counter;
}


int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <barrier-name> <size>\n", argv[0]);
		return 1;
	}
	char* name = argv[1];
	int size = atoi(argv[2]);
	if (size <= 0) {
		fprintf(stderr, "Size has to be a valid number larger than one.\n");
		return 1;
	}
	char* request_fifo;
	char* release_fifo;
	if ( (request_fifo = create_request_fifo(name)) == NULL ) {
		fprintf(stderr, "Error while creating the request fifo.\n");
		return 1;
	}
	fprintf(stdout, "Created %s\n", request_fifo);
	if ( (release_fifo = create_release_fifo(name)) == NULL ) {
		fprintf(stderr, "Error while creating the release fifo.\n");
		return 1;
	}
	fprintf(stdout, "Created %s\n", release_fifo);
	char buffer[size];
	int request_fd = -1;
	int release_fd = -1;
	for (;;) {
		fprintf(stdout, "Going to open the request fifo '%s' for reading.\n", request_fifo);
		if ( (request_fd = open(request_fifo, O_RDONLY)) < 0) {
			fprintf(stderr, "An error occured while opening the request fifo.\n");
			return 1;
		}
		fprintf(stdout, "Going to read %d bytes.\n", size);
		if (read_until(request_fd, &buffer, size) <= 0) {
			close(request_fd);
			fprintf(stderr, "An error occurred while reading from the request fifo.\n");
			return 1;
		}
		close(request_fd);
		fprintf(stdout, "Read %d bytes, releasing now.\n", size);
		if ( (release_fd = open(release_fifo, O_WRONLY)) == -1) {
			fprintf(stderr, "Could not open the release fifo %s for writing.\n", release_fifo);
			return 1;
		}
		if (write(release_fd, &buffer, size) < 0) {
			fprintf(stderr, "Could not write to the release fifo.\n");
			close(release_fd);
			return 1;
		}
		fprintf(stdout, "Released the barrier.\n");
		close(release_fd);
	}
	return 0;
}
