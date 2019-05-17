#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    char buffer[256];
    pid_t cp = getpid();
    printf("Process ID: %d\n", cp);
    char* name = "Peyman";
    int fd[2];
    pipe(fd);
    ssize_t wbytecount = write(fd[1], name, 6);
    printf("Wrote %ld bytes to the write channel of the pipe.\n", wbytecount);
    ssize_t rbytecount = read(fd[0], buffer, 256);
    printf("Read %ld bytes from the read channel of the pipe.\n", rbytecount);
    buffer[rbytecount] = '\0';
    printf("%s\n", buffer);
    dup2(fd[1], STDOUT_FILENO);
    name = "hi\0";
    write(STDOUT_FILENO, name, 6);
    read(fd[0], buffer, 256);
    fprintf(stderr, "%s\n", buffer);
    return EXIT_SUCCESS;
}