#pragma once

#include <cstddef>
#include <vector>
#include <string>

#include "macros.h"

namespace Common {
template<typename T>
class MemPool final {
public:
  explicit MemPool(std::size_t size) : store_(size) {
    ASSERT(reinterpret_cast<const ObjectBlock *>(&(store_[0].object_)) == &(store_[0]),
           "Object should be laid out in memory before is_free");
  }

  MemPool() = delete;

  MemPool(const MemPool &) = delete;

  MemPool(MemPool &&) = delete;

  MemPool &operator=(const MemPool &) = delete;

  MemPool &operator=(MemPool &&) = delete;

  template<typename... Args>
  T *allocate(Args... args) noexcept {
    auto free_block_index = find_free_block();
    auto &block = store_[free_block_index];
    T *ret = new(&(block.object_)) T(args...);
    block.is_free = false;

    return ret;
  }

  void deallocate(const T *obj) noexcept {
    const auto block_index = (reinterpret_cast<const ObjectBlock *>(obj) - &store_[0]);
    ASSERT(block_index >= 0 && static_cast<std::size_t>(block_index) < store_.size(), "Element being deallocated does not belong to this MemPool.");
    ASSERT(!store_[block_index].is_free, "Expected element being deallocated to be in-use.");
    store_[block_index].is_free = true;
    obj->~T();
  }

private:
  struct ObjectBlock {
    T object_;
    bool is_free = true;
  };

  std::vector<ObjectBlock> store_;
  std::size_t next_free_index = 0;

  std::size_t find_free_block() noexcept {
    const auto initial_free_index = next_free_index;
    while (!store_[next_free_index].is_free) {
      ++next_free_index;
      if (UNLIKELY(next_free_index >= store_.size())) {
        next_free_index = 0;
      }
      if (UNLIKELY(next_free_index == initial_free_index)) {
        ASSERT(false, "No free block found.");
      }
    }
    return next_free_index;
  }
};
}
