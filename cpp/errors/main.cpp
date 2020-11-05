#include <iostream>
#include <system_error>
#include <type_traits>


enum ValidationError {
  IncorrectType = 1,
  ValueError = 2,
};


class ValidationCategory : public std::error_category {
public:
  const char* name() const noexcept override { return "validation"; }
  std::string message(int event) const override {
    switch (static_cast<ValidationError>(event)) {
      case ValidationError::IncorrectType:
        return "Input is of the incorrect type.";
      case ValidationError::ValueError:
        return "Input is of the correct format but the insupported value.";
      default:
        return "unknown";
    }
  };
};


enum AuthenticationError {
  Unauthorized = 1,
  Forbidden,
};


class AuthenticationCategory : public std::error_category {
public:
  const char* name() const noexcept override { return "auth"; }
  std::string message(int event) const override {
    switch (static_cast<AuthenticationError>(event)) {
      case AuthenticationError::Unauthorized:
        return "You are not authorized at all.";
      case AuthenticationError::Forbidden:
        return "Permission denied.";
      default:
        return "unknown";
    }
  };
};

namespace std {
  template<>
  struct is_error_code_enum<ValidationError> : true_type {};

  template<>
  struct is_error_code_enum<AuthenticationError> : true_type {};
}

std::error_code make_error_code(ValidationError e) {
  static ValidationCategory category;
  return {static_cast<int>(e), category};
}

std::error_code make_error_code(AuthenticationError e) {
  static AuthenticationCategory category;
  return {static_cast<int>(e), category};
}

int main(int argc, char *argv[])
{
  std::error_code ec = ValidationError::IncorrectType;
  std::cout << ec << std::endl;
  std::error_code ec2 = AuthenticationError::Forbidden;
  std::cout << ec2 << std::endl;
  return 0;
}
