#include <iostream>


template<typename T>
class Holder {
private:
  T value_;

public:
  explicit Holder(T&& value) : value_(std::move(value)) {}

  friend std::ostream& operator << (std::ostream& output, const Holder& stack) {
    output << stack.value_;
    return output;
  }
};

int main() {
  Holder<int> a(12);
  std::cout << "Value is : " << a << std::endl;
}
