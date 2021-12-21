#ifndef LLVM_BUILTINS_HPP
#define LLVM_BUILTINS_HPP

#include "../value.hpp"
#include "../namespace.hpp"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

namespace llvm {
  class Module;
  class Type;
}

extern "C" DLLEXPORT LLVMToy::Value lt_builtin_set_var(LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_get_var(LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_puts(LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_puts2(LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_puts3(LLVMToy::Value, LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_binop(LLVMToy::Value, LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_unop(LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_truthy(LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_build_pointer(uint8_t, void*);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_closure_read(LLVMToy::Value, LLVMToy::Value);
extern "C" DLLEXPORT LLVMToy::Value lt_builtin_closure_write(LLVMToy::Value, LLVMToy::Value, LLVMToy::Value);

namespace LLVMToy {
  class LLVMBuiltins {
    public:
      static void add_builtins(llvm::Module*, llvm::Type*);
      static void add_builtin(llvm::Module*, llvm::Type*, string, int);
  };
}

#endif