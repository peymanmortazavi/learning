#include <iostream>

using namespace std;

class SomeClass;

class Forward {
public:

  template<typename Callable>
  int call(Callable c) {
    return c->call() + 10;
  }

};

class SomeClass
{
public:
  SomeClass(int value) : value_(value) {}
  int call() { return value_; }
  int apply() { return Forward().call(this); }

private:
  int value_ = 0;
};


int main(int argc, char *argv[])
{
  SomeClass x{15};
  std::cout << x.apply() << std::endl;
  return 0;
}
