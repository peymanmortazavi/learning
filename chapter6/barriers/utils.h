#ifndef UTILS_H
#define UTILS_H

char* get_request_barrier(char* name);
char* get_release_barrier(char* name);

char* create_request_fifo(char* name);
char* create_release_fifo(char* name);

#endif
