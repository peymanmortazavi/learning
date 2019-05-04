#include "vector.h"
#include <string.h>


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


void vec_add(vector_t* self, char* name, size_t requirement) {
  if (vec_find(self, name) != NULL) return;

  node_t* item = malloc(sizeof(node_t));
  item->counter = 0;
  item->name = name;
  item->next = NULL;
  item->requirement = requirement;

  if (self->head == NULL) {
    self->head = item;
  } else {
    node_t* cursor = self->head;
    while(cursor->next != NULL) cursor = cursor->next;
    cursor->next = item;
  }
  self->len++;
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