#include <stdlib.h>
#include "queue.h"


void queue_init(queue_t* this) {
  this->head = NULL;
  this->length = 0;
}

int queue_empty(queue_t* this) {
  return !this->length;
}

int enq(queue_t* this, char* path) {
  // we need to find the tail.
  node_t* cursor = this->head;
  node_t* item = malloc(sizeof(node_t));
  item->path = path;
  item->next = NULL;
  if (cursor == NULL) {  // head case.
    this->head = item;
    this->length = 1;
    return 0;
  }
  while(cursor->next != NULL) cursor = cursor->next;
  cursor->next = item;
  this->length++;
  return 0;
}

char* deq(queue_t* this) {
  if (this->head != NULL) {
    char* result = this->head->path;
    node_t* cursor = this->head;
    this->head = cursor->next;
    this->length--;
    free(cursor);
    return result;
  }
  return NULL;
}