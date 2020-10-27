#include "cpplib_interface.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  struct int_map_t map;
  int_map_init(&map);
  int_map_insert(&map, "Peyman", 12);
  int* result = int_map_get(&map, "Peyman");
  if (result != 0) {
    printf("Result is: %d\n", *result);
  }
  int_map_delete(&map);
  return 0;
}
