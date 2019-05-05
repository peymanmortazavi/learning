#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "vector.h"


void vec_init(vector_t* self) {
  self->head = NULL;
  self->len = 0;
}


node_t* vec_find(vector_t* self, char* name) {
  node_t* cursor = self->head;
  while(cursor != NULL) {
    if (strcmp(cursor->name, name) == 0) return cursor;
    cursor = cursor->next;
  }
  return NULL;
}


int vec_add(vector_t* self, char* name, pid_t proc) {
  if (vec_find(self, name) != NULL) return -1;

  node_t* item = malloc(sizeof(node_t));
  item->name = name;
  item->next = NULL;
  item->process_id = proc;

  if (self->head == NULL) {
    self->head = item;
  } else {
    node_t* cursor = self->head;
    while(cursor->next != NULL) cursor = cursor->next;
    cursor->next = item;
  }
  self->len++;
  return 0;
}


void vec_del(vector_t* self, node_t* node) {
  node_t* cursor = self->head;
  if (cursor == NULL || node == NULL) return;
  while(cursor->next != node && cursor->next != NULL) {
    cursor = cursor->next;
  }
  cursor->next = node->next;
  free(node->name);
  free(node);
  self->len--;
}


void vec_dyn_iter(vector_t* self, int(*cb)(node_t* node)) {
  node_t* cursor = self->head;
  node_t* prior = NULL;
  while(cursor != NULL) {
    if (cb(cursor) != 0) {
      // it means we have to delete this.
      if (prior == NULL) {  // it means we're at HEAD.
        self->head = cursor->next;
      } else {
        prior->next = cursor->next;  
      }
      self->len--;
      free(cursor->name);
      node_t* tmp = cursor;
      cursor = cursor->next;
      free(tmp);
    } else {
      cursor = cursor->next;
    }
  }
}