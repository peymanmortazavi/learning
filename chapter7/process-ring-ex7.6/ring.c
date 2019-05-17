#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void process(int id) {
    for(int i = 0; i < 10; i++) {
        int result;
        write(STDOUT_FILENO, &i, sizeof(i));
        ssize_t rc = read(STDIN_FILENO, &result, sizeof(result));
        fprintf(stderr, "OUTPUT @ %d: %d\n", id, result);
    }
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
    process(id);
    return EXIT_SUCCESS;
}