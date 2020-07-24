#include <iostream>
#include <concepts>
#include <type_traits>
#include <iterator>

using namespace std;


class ForwardIterator {
public:

  using iterator_category = std::forward_iterator_tag;
  using value_type = int;
  using difference_type = int;

  explicit ForwardIterator() : value_(0) {}
  explicit ForwardIterator(int value) : value_(value) {}

  ForwardIterator& operator ++ () { value_++; return *this; }
  ForwardIterator operator ++ (int) { auto it = *this; this->value_++; return it; }
  bool operator == (const ForwardIterator& rhs) const { return value_ == rhs.value_; }
  bool operator != (const ForwardIterator& rhs) const { return !(rhs == *this); }

  int operator * () const {
    return value_;
  }

private:
  int value_ = 0;
};


template<forward_iterator T>
void iterate(T iterator) {
  for(auto i = 0; i <= 10; i++) {
    std::cout << *(iterator++) << std::endl;
  }
}


int main(int argc, char *argv[])
{
  auto it = ForwardIterator(25);
  iterate(it);
  return 0;
}
