#pragma once
#include <string>
#include <string_view>

template <typename T> concept Str = requires(T s) { std::string_view(s); };

template <Str... S> std::string fmt(std::string_view format, S... strs) {
  std::string result;

  auto extend = [&format, &result](auto &&str) {
    auto pos = format.find("{}");
    result += format.substr(0, pos);
    result += str;
    format = format.substr(pos + 2);
  };

  (extend(strs), ...);

  return result;
}