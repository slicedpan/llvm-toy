#ifndef FUNCTION_OBJECT_HPP
#define FUNCTION_OBJECT_HPP

#include <cstdint>

namespace LLVMToy {
  struct FunctionObject {
    void* pointer;
    uint32_t arity;
    uint32_t padding;
  };
}

#endif