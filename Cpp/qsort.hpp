#include <algorithm>
#include <bits/c++config.h>
#include <random>
template <typename T> concept Data = requires(T a, T b) { a < b; };

template <Data T> std::size_t partition(T *data, std::size_t p, std::size_t r) {
  T x = data[r];
  int i = p - 1;
  for (auto j = p; j <= r - 1; j++) {
    if (data[j] < x) {
      i++;
      std::swap(data[j], data[i]);
    }
  }
  i++;
  std::swap(data[i], data[r]);
  return i;
}

template <Data T>
std::size_t randomizedPartition(T *data, std::size_t p, std::size_t r) {
  std::random_device rand;
  std::default_random_engine e(rand());
  std::uniform_int_distribution<int> uniform_dist(p, r);
  int i = uniform_dist(e);
  std::swap(data[i], data[r]);
  return partition(data, p, r);
}

template <Data T> void qsort(T *data, std::size_t p, std::size_t r) {
  if (p < r) {
    auto q = partition(data, p, r);
    qsort(data, p, q - 1);
    qsort(data, q + 1, r);
  }
}

template <Data T> void randomizedQsort(T *data, std::size_t p, std::size_t r) {
  if (p < r) {
    auto q = randomizedPartition(data, p, r);
    randomizedQsort(data, p, q - 1);
    randomizedQsort(data, q + 1, r);
  }
}