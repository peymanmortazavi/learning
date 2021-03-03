#include <iostream>


/*
 * Variadic Template
 */
void print() {}  // basic case without any types.

template<typename Arg, typename... Args>
void print(Arg arg, Args... args) {
  std::cout << arg << std::endl;
  print(args...);
}

template<char, typename Arg>
void print_separator(Arg arg) {
  std::cout << arg << std::endl;
}

template<char Separator, typename Arg, typename... Args>
void print_separator(Arg arg, Args... args) {
  std::cout << arg << Separator;
  print_separator<Separator>(args...);
}


/*
 * sizeof... expression gives you the compile time count of a parameter pack.
 */
template<typename... Types>
void how_many_types() {
  std::cout << "Received " << sizeof...(Types) << " Types here :)" << std::endl;
}


/*
 * Fold Expressions
 */
template<typename... Args>
auto fold_sum(Args... args) {
  return (... + args);
}


/*
 * Utilize the friend method for operator << and == or other things used for similar purpose.
 */
template<typename T>
class Holder {
private:
  T value_;

public:
  explicit Holder(T&& value) : value_(std::move(value)) {}

  // This is much easier than having to define this outside of the class definition.
  friend std::ostream& operator << (std::ostream& output, const Holder& stack) {
    output << stack.value_;
    return output;
  }
};

int main() {
  Holder<int> a(12);
  std::cout << "Value is : " << a << std::endl;

  print(a, "hello", 12);  // use the variadic method.
  print_separator<','>(a, "hello", 12);  // Custom separator.
  print_separator<'|'>(a, "world", 36);  // Custom separator.

  how_many_types<int, double, char>();

  std::cout << "Fold Sum Result: " << fold_sum(1, 2, 3, 4, 5) << std::endl;
}
