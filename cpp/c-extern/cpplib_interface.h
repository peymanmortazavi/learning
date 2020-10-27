#if __cplusplus
extern "C" {
#endif

  struct int_map_t {
    void* storage;  //cpp::Storage<int> storage;
  };

  void int_map_init(struct int_map_t* map);
  void int_map_insert(struct int_map_t* map, const char* name, int value);
  int* int_map_get(struct int_map_t* map, const char* name);
  void int_map_delete(struct int_map_t* map);

#if __cplusplus
}
#endif
