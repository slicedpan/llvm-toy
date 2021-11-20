#ifndef LLVM_BUILTINS_HPP
#define LLVM_BUILTINS_HPP

#include "../value.hpp"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

namespace llvm {
  class Module;
}

extern "C" DLLEXPORT LLVMToy::Value lt_builtin_puts(LLVMToy::Value);

namespace LLVMToy {
  class LLVMBuiltins {
    public:
      static void add_builtins(llvm::Module*);
  };
}

#endif