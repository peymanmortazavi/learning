#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>

#include "utils.h"
#include "vector.h"


void process_barrier(char* name) {
    fprintf(stdout, "[%s] About to sleep 2 seconds.\n", name);
    sleep(2);
    fprintf(stdout, "[%s] alright, here it is. killing it.\n", name);
}


int should_keep_node(node_t* node) {
    int status;
    if (waitpid(node->process_id, &status, WNOHANG) != 0) {
        fprintf(stdout, "Killing %s\n", node->name);
        return 1;
    }
    fprintf(stdout, "Ignoring %s\n", node->name);
    return 0;
}


void listen(char* request_filename) {
    vector_t vec;
    vec_init(&vec);
    char buffer[NAME_MAX + 1];

    int request_fd;

    for(;;) {
        if ( (request_fd = open(request_filename, O_RDONLY)) == -1) {
            fprintf(stderr, "Could not open the file: %s\n", strerror(errno));
            return;
        }
        for (;;) {
            fprintf(stdout, "Waiting for barrier requests...\n");
            ssize_t read_bytes;
            if ( (read_bytes = read(request_fd, buffer, NAME_MAX + 1)) < 0) {
                fprintf(stderr, "Could not read from the file: %s\n", strerror(errno));
                return;
            }
            if (read_bytes == 0) {
                // end of file, this is where we actually need to close the file and open it again.
                fprintf(stdout, "no file is currently writing to this fifo %s, closing it.\n", request_filename);
                break;
            }
            if (read_bytes < 2) {
                fprintf(stderr, "Invalid request: @%ld", read_bytes);
                write(STDOUT_FILENO, buffer, read_bytes);
                fprintf(stderr, "\n");
                continue;
            }
            int count = buffer[0];
            char* name = malloc(read_bytes*sizeof(char));
            memcpy(name, buffer + 1, read_bytes-1);
            name[read_bytes] = 0;
            printf("Received request to create barrier %s with len %d\n", name, count);
            vec_dyn_iter(&vec, should_keep_node);
            if (vec_find(&vec, name) == NULL) continue;
            pid_t child_pid = fork();
            if (child_pid == 0) {
                process_barrier(name);
                exit(0);
            } else {
                vec_add(&vec, name, child_pid);
            }
            vec_dyn_iter(&vec, should_keep_node);
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <name>\n", argv[0]);
        return 1;
    }
    char* request_filename;
    if ( (request_filename = create_request_fifo(argv[1])) == NULL) {
        fprintf(stderr, "Cannot create request fifo.\n");
        return 1;
    }
    listen(request_filename);
    return 0;
}