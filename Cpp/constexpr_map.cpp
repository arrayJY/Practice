#include <algorithm>
#include <array>
#include <string_view>
#include <utility>

template <typename Key, typename Value, std::size_t N> struct ConstexprMap {
  std::array<std::pair<Key, Value>, N> _value;
  std::size_t _i = 0;

  template <typename... K, typename... V>
  constexpr ConstexprMap(std::pair<K, V>... paris) {
    (insert_impl(paris), ...);
  };

  constexpr void insert_impl(std::pair<Key, Value> pairs) {
    _value.at(_i).first = pairs.first;
    _value.at(_i).second = pairs.second;
    _i++;
  }

  constexpr Value at(const Key &key) const {
    return std::find_if(_value.begin(), _value.end(),
                        [key](const auto &pair) { return pair.first == key; })
        ->second;
  }
};

template <typename Key, typename Value, typename... Pair>
constexpr auto makeMap(Pair const &... paris) {
  return ConstexprMap<Key, Value, sizeof...(paris)>(paris...);
};

int main() {
  constexpr auto map = makeMap<std::string_view, int>(
      std::make_pair("a", 1), std::make_pair("b", 2), std::make_pair("c", 3),
      std::make_pair("d", 4), std::make_pair("f", 5));

  static_assert(map.at("a") == 1, "Get a wrong value.");
  static_assert(map.at("b") == 2, "Get a wrong value.");
  static_assert(map.at("c") == 3, "Get a wrong value.");
  static_assert(map.at("d") == 4, "Get a wrong value.");
  static_assert(map.at("f") == 5, "Get a wrong value.");
}