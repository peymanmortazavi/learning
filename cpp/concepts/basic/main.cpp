#include <iostream>
//#include <concepts>
//#include <type_traits>

using namespace std;


template<typename X> using NameOf = typename X::name;


template<typename T>
concept Drawable = requires (T t) {
  typename NameOf<T>;

  { t.Draw() };

};


template<typename T>
concept DetailDrawable = Drawable<T> && requires(const T& t) {
  { t.DetailDraw() } -> std::convertible_to<int>;
};


//template<DetailDrawable T>
void test(DetailDrawable auto a) {
  a.Draw();
  a.DetailDraw();
}

struct some {
  void Draw() {
    std::cout << "Some" << std::endl;
  }
};


struct some_other {
  typedef int name ;
  int Draw() {
    std::cout << "Some other" << std::endl;
    return 10;
  }
  int DetailDraw() const {
    return 0;
  }
};


int main(int argc, char *argv[])
{
  //test(some{});
  test(some_other{});
  std::cout << "Welcome to concepts 2020" << std::endl;
  return 0;
}
