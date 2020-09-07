#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T> concept Data = requires(T v) { std::cout << v; };

template <Data T> class Heap {
public:
  Heap() : _data{T{}} {};
  Heap(const std::initializer_list<T> &data) : _data(data) {
    _data.insert(_data.begin(), T{});
    _buildMaxHeap();
  }
  void push(const T &e) {
    _data.push_back(e);
    _buildMaxHeap();
  };
  void pop() {
    _data.erase(_data.begin() + 1);
    _buildMaxHeap();
  }
  T maximum() const { return _data[1]; }
  auto sort() {
    std::vector<T> r{};
    for (auto i = _data.size() - 1; i >= 1; i--) {
      std::swap(_data[1], _data[i]);
      r.push_back(_data[i]);
      _data.pop_back();
      _maxHeapify(1);
    }
    return r;
  };
  void print(std::size_t i = 1) {
    if (i >= _data.size())
      return;
    for (unsigned m = log2(i); m > 0; m--) {
      std::cout << "|\t";
    }
    std::cout << "└─" << _data[i] << "\n";

    print(i * 2);     // dfs left
    print(i * 2 + 1); // dfs right
  };

private:
  void _maxHeapify(std::size_t i = 1) {
    auto left = i * 2, right = i * 2 + 1, heapSize = _data.size() - 1;
    auto largest = i;
    largest = left <= heapSize && _data[left] > _data[i] ? left : i;
    largest =
        right <= heapSize && _data[right] > _data[largest] ? right : largest;
    if (largest != i) {
      std::swap(_data[i], _data[largest]);
      _maxHeapify(largest);
    }
  }
  void _buildMaxHeap() {
    for (auto i = (_data.size() - 1) / 2; i >= 1; i--) {
      _maxHeapify(i);
    }
  }
  std::vector<T> _data;
};