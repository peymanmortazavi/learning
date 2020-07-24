#include <sys/stat.h>
#include <errno.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils.h"


char* make_name(char* name, char* type) {
  char* fifo_name = malloc(NAME_MAX * sizeof(char));
  size_t len = strlen(name);
  strcpy(fifo_name, name);
  strcat(fifo_name, type);
  fifo_name[len + strlen(type)] = 0;
  return fifo_name;
}


char* get_request_barrier(char* name) {
  return make_name(name, ".request");
}

char* get_release_barrier(char* name) {
  return make_name(name, ".release");
}


char* create_request_fifo(char* name) {
  char* fifo_name = make_name(name, ".request");
  if( (mkfifo(fifo_name, S_IWGRP | S_IWUSR | S_IWOTH | S_IRUSR)) == -1 && errno != EEXIST) {
    return NULL;
  }
  return fifo_name;
}


char* create_release_fifo(char* name) {
  char* fifo_name = make_name(name, ".release");
  if( (mkfifo(fifo_name, S_IRGRP | S_IRUSR | S_IROTH | S_IWUSR)) == -1 && errno != EEXIST) {
    return NULL;
  }
  return fifo_name;
}