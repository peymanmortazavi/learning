#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

typedef struct node_t {
  struct node_t* next;
  char* path;
} node_t;

typedef struct queue_t {
  node_t* head;
  size_t length;
} queue_t;

void queue_init(queue_t* this);
int queue_empty(queue_t* this);
int enq(queue_t* this, char* path);
char* deq(queue_t* this);

#endif