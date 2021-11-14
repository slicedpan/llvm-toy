#ifndef MEMORY_ALLOCATION_HPP
#define MEMORY_ALLOCATION_HPP

#include <cstddef>

namespace LLVMToy {
  void* allocate(size_t bytes);
  void* reallocate(void* ptr, size_t bytes);
  void deallocate(void* ptr);
}

#endif