#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

namespace cpp {

  template<typename T>
  class Storage {
  public:

    void insert(const char* name, const T& value) {
      mapping_.push_back(Mapping{name, value});
    }

    T* get(const char* name) {
      auto it = std::find_if(begin(mapping_), end(mapping_), [name](const auto& item){
          return strcmp(name, item.key.c_str()) == 0;
      });
      if (it != end(mapping_)) return &it->value;
      return nullptr;
    }

  private:
    struct Mapping {
      std::string key;
      T value;
    };

    std::vector<Mapping> mapping_;
  };

}
