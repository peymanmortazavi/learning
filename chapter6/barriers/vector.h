#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef struct node_t {
  struct node_t* next;
  char* name;
  size_t requirement;
  size_t counter;
} node_t;


typedef struct vector_t {
  struct node_t* head;
  size_t len;
} vector_t;


void vec_init(vector_t* self);
node_t* vec_find(vector_t* self, char* name);
void vec_add(vector_t* self, char* name, size_t requirement);
void vec_del(vector_t* self, node_t* node);


#endif