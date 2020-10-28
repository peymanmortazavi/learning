# How to handle errors

There are a couple of ways to thinkg about this.

## 1. Using the exceptions

This is quite popular with a lot of the new languages like Python, C# and Java.
But it has its own drawbacks. Google, for instance, discourages use of
Exceptions altoghether.

## 2. Using error codes in return values

This is a very familiar pattern for C developers but it makes it diffcult to
return complex structures as you may only return the error code. The result must
be out-variable.

## 3. You can take the pattern in (2) and take the error code as out-variable.

This has similar issues but it solves one thing, you can now return more complex values.


## 4. Use of Either pattern

You can use other libraries for this or make your own. At the end of the day, we need to
define functions so they return `expected<result, error_description>`.

It could return an object and from there we could use lambdas to deal with the error.

```cpp
expected<std::string, int> divide(int a, int b) {
    if (b == 0) return unexpected<10>;  // say 10 is error code for divide by 0.
    else return a / b;
}

auto result = divide(10, 0).then([](auto value){ return value; }).error([](auto error){ return 0; });
```

# Reads

https://akrzemi1.wordpress.com/2017/07/12/your-own-error-code/
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4109.pdf
https://hackernoon.com/error-handling-in-c-or-why-you-should-use-eithers-in-favor-of-exceptions-and-error-codes-f0640912eb45
