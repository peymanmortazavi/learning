#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int* calc_next(int id) {
    char* buffer = malloc(256 * sizeof(buffer));
    ssize_t rbytecount = read(STDIN_FILENO, buffer, 256);
    buffer[rbytecount] = 0;
    fprintf(stderr, "%d: got %s\n", id, buffer);
    int* result = malloc(2 * sizeof(int));
    for(unsigned int index = 0; index < rbytecount; index++) {
        if (buffer[index] == ' ') {
            buffer[index] = 0;
            result[0] = atoi(buffer + index + 1);
            result[1] = atoi(buffer) + result[0];
            buffer[index] = ' ';
            break;
        }
    }
    free(buffer);
    return result;
}


void process_client(int id) {
    char* buffer = malloc(256 * sizeof(char));
    int* numbers = calc_next(id);
    int count = sprintf(buffer, "%d %d", numbers[0], numbers[1]);
    buffer[count] = 0;
    ssize_t wbytecount = write(STDOUT_FILENO, buffer, count);
    fprintf(stderr, "%d: wrote %s which is %ld bytes to the next item.\n", id, buffer, wbytecount);
    free(buffer);
    free(numbers);
}


void process_server(int id) {
    static char* starting_point = "1 1";
    ssize_t wbytecount = write(STDOUT_FILENO, starting_point, 3);
    fprintf(stderr, "server wrote %ld bytes.\n", wbytecount);
    int* numbers = calc_next(id);
    fprintf(stderr, "RESULT: %d\n", numbers[1]);
    free(numbers);
}


int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int nproc = atoi(argv[1]);
    int fd[2];
    pipe(fd);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    int id = 0;
    while (id < nproc -1) {
        pipe(fd);
        if (fork() == 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            id++;
        } else {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            break;
        }
    }
    if (id == 0) {
        process_server(id);
    } else {
        process_client(id);
    }
    return EXIT_SUCCESS;
}