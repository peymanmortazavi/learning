#include <iostream>
#include <concepts>
#include <type_traits>
#include <string.h>

using namespace std;


template<typename X> using NameOf = typename X::name;


template<typename T>
concept Drawable = requires (T t) {
  typename NameOf<T>;

  { t.Draw() };

};

template<typename T>
constexpr bool has_name() { return false; }

template<typename T> requires requires (T t) { { t.get_name() } -> std::convertible_to<std::string>; }
constexpr bool has_name() { return true; }

template<class, class = void>
struct is_int_constructible : std::false_type{};

template<typename T>
struct is_int_constructible<T, std::void_t<decltype(T(declval<int>()))>> : std::true_type{};

template<typename T>
concept DetailDrawable = Drawable<T> && requires(const T& t) {
  { t.DetailDraw() } -> std::convertible_to<int>;
};

template<Drawable T>
void test(T drawable) {
  drawable.Draw();
}

void test2(DetailDrawable auto a) {
  a.Draw();
  a.DetailDraw();
}


template<Drawable T>
void test3(T d) {
  // Even though the check below is a constant expression and will
  // get optimized away, if you use d.DetailDraw() it would fail.
  if (DetailDrawable<T>) {
    printf("it is DetailDrawable\n");
  }
  d.Draw();
}

template<Drawable T>
void test3_optimized(T d) {
  d.Draw();
}

template<DetailDrawable T>
void test3_optimized(T d) {
  d.DetailDraw();
}

struct some {
  using name = int;
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

template<typename T> requires is_int_constructible<T>::value
T test4(int input) { return T(input + 10); }


struct int_lover {
  int x;
};


template< typename T, typename G >
static inline
std::enable_if_t<std::is_integral_v<G>, bool>
is_equal(const T& t, G value) {
  return value == t;
}

template< typename T, typename G >
static inline
std::enable_if_t<std::is_same_v<G, const char*>, bool>
is_equal(const T& t, G value) {
  return strcmp(t, value) == 0;
}


int main(int argc, char *argv[])
{
  // test only needs a Drawable
  test(some{});

  // test2 accepts only a DetailDrawable
  test2(some_other{});

  // test3 supports both Drawable and DetailDrawable
  test3(some{});
  test3(some_other{});

  test3_optimized(some{});
  test3_optimized(some_other{});

  auto x = test4<int_lover>(24);
  printf("number is %d\n", x.x);
  std::cout << "Welcome to concepts 2020" << std::endl;

  std::cout << is_equal("Peyman", "Peyman") << std::endl;
  std::cout << is_equal(12, 12) << std::endl;
  return 0;
}
