#include <iostream>
#include "cpplib.h"
#include "cpplib_interface.h"

using namespace cpp;

int main(int argc, char *argv[])
{
  int_map_t map;
  int_map_init(&map);
  int_map_insert(&map, "Peyman", 12);
  if (auto result = int_map_get(&map, "Peyman")) {
    std::cout << "Result is: " << *result << std::endl;
  }
  int_map_delete(&map);
  return 0;
}
