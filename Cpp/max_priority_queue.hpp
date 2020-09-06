#include "heap.hpp"
#include <bits/c++config.h>
#include <compare>
#include <ostream>
#include <sstream>

template <typename T> class mQueue {
public:
  mQueue<T>() : _heap{} {}
  void insert(const std::size_t key, T value) {
    _heap.push(_Data{key, value});
  };
  T maximum() const { return _heap.maximum().value; };
  T extractMax() {
    T r = _heap.maximum().value;
    _heap.pop();
    return r;
  };
  void print() { _heap.print(); }

private:
  struct _Data {
    std::size_t key;
    T value;
    constexpr auto operator>(const _Data &other) { return key > other.key; }
    constexpr auto operator<(const _Data &other) { return key < other.key; }
    _Data() : key{}, value{} {}
    _Data(const std::size_t k, const T &v) : key(k), value(v) {}
    friend std::ostream &operator<<(std::ostream &o, const _Data &v) {
      o << "{ " << v.key << ":" << v.value << " }";
      return o;
    }
  };
  Heap<_Data> _heap;
};
