#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "utils.h"


int create_request_fifo(char* filename) {
    int result;
    while ((result = mkfifo(filename, S_IRWXU | S_IWGRP | S_IWOTH)) != 0 && errno == EINTR);
    if (result != 0 && errno != EEXIST) {
        return result;
    }
    return 0;
}

int create_response_fifo(char* filename) {
    int result;
    while ((result = mkfifo(filename, S_IRWXU | S_IRGRP | S_IROTH)) != 0 && errno == EINTR);
    if (result != 0 && errno != EEXIST) {
        return result;
    }
    return 0;
}