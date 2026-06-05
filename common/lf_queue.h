#pragma once

#include <iostream>
#include <vector>
#include <atomic>

#include "macros.h"

namespace Common {
template<typename T>
class LFQueue final {
public:
  explicit LFQueue(std::size_t num_elems) :
      store_(num_elems, T()) /* initialize elements to avoid undefined behavior */ {
  }

  LFQueue() = delete;

  LFQueue(const LFQueue &) = delete;

  LFQueue(LFQueue &&) = delete;

  LFQueue &operator=(const LFQueue &) = delete;

  LFQueue &operator=(LFQueue &&) = delete;

  auto getNextToWriteTo() noexcept {
    return &store_[next_write_index_];
  }

  auto updateWriteIndex() noexcept {
    next_write_index_ = (next_write_index_ + 1) % store_.size();
    num_elements_++;
  }

  auto getNextToRead() const noexcept {
    return (size() > 0) ? &store_[next_read_index_] : nullptr;
  }

  auto updateReadIndex() noexcept {
    next_read_index_ = (next_read_index_ + 1) % store_.size();
    num_elements_--;
  }

  auto size() const noexcept {
    return num_elements_.load();
  }

private:
  std::vector<T> store_;

  std::atomic<std::size_t> next_write_index_{0};
  std::atomic<std::size_t> next_read_index_{0};

  std::atomic<std::size_t> num_elements_{0};
};
}
