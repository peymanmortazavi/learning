#include "cpplib.h"
#include "cpplib_interface.h"

using IntStorage = cpp::Storage<int>;

IntStorage* get_map(struct int_map_t* map) {
  return reinterpret_cast<IntStorage*>(map->storage);
}

extern "C" void int_map_init(struct int_map_t* map) {
  map->storage = new IntStorage();
}

extern "C" void int_map_insert(struct int_map_t* map, const char* name, int value) {
  get_map(map)->insert(name, value);
}

extern "C" int* int_map_get(struct int_map_t* map, const char* name) {
  return get_map(map)->get(name);
}

extern "C" void int_map_delete(struct int_map_t* map) {
  //delete map;
}
