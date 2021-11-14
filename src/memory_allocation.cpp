#include "memory_allocation.hpp"
#include <malloc.h>

namespace LLVMToy {
  void* allocate(size_t size) {
    return malloc(size);
  }

  void* reallocate(void* ptr, size_t size) {
    return realloc(ptr, size);
  }

  void deallocate(void* ptr) {
    free(ptr);
  }
}