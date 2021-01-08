#include <iostream>
#include <string.h>
#include <type_traits>

using namespace std;


template<typename T>
class DataHolder {
public:
  using ValueType = std::conditional_t<
    std::is_integral<T>::value,
    T,
    std::add_const_t<std::add_lvalue_reference_t<T>>
  >;

  DataHolder(ValueType value) : value_(value) {}

  bool Equal() {
    return DataHolder::equal(value_);
  }

  ValueType get_value() const { return value_; }

private:
  ValueType value_;

  template<typename F>
  static inline
  std::enable_if_t<std::is_integral<F>::value, bool>
  equal (const F& f) {
    std::cout << "Int" << std::endl;
    return f == 24;
  }

  template<typename F>
  static inline
  std::enable_if_t<std::is_floating_point<F>::value, bool>
  equal (const F& f) {
    std::cout << "Float" << std::endl;
    return false;
  }

  template<typename F>
  static inline
  std::enable_if_t<std::is_class<F>::value, bool>
  equal (const F& f) {
    std::cout << "Generic" << std::endl;
    return false;
  }
};

struct ComplexObject {
  int age;
  const char* name;
};

int main(int argc, char *argv[])
{
  int a = 24;
  ComplexObject c{24, "Peyman"};
  DataHolder<ComplexObject> z1 {c};
  DataHolder<int> z2 {a};
  a = 30;
  c.age = 30;

  std::cout << z1.get_value().age << std::endl; // const reference
  std::cout << z2.get_value() << std::endl; // copy by value
  std::cout << z1.Equal() << std::endl;
  std::cout << z2.Equal() << std::endl;

  return 0;
}
