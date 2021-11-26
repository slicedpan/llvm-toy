#include "debug_printer.hpp"
#include <cstdio>
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

extern "C" DLLEXPORT void lt_debug_print_i1(bool val) {
  printf("i1:%d\n", val);
}
extern "C" DLLEXPORT void lt_debug_print_i8(int8_t val) {
  printf("i8:%d\n", val);
}
extern "C" DLLEXPORT void lt_debug_print_i32(int32_t val) {
  printf("i32:%d\n", val);
}
extern "C" DLLEXPORT void lt_debug_print_i64(int64_t val) {
  printf("i64:%ld\n", val);
}

void register_debug_functions(llvm::Module* module) {
  llvm::LLVMContext& ctx = module->getContext();
  llvm::FunctionType* fn_type = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), llvm::ArrayRef<llvm::Type*>{llvm::Type::getInt1Ty(ctx)}, false);
  llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, "lt_debug_print_i1", *module);

  fn_type = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), llvm::ArrayRef<llvm::Type*>{llvm::Type::getInt8Ty(ctx)}, false);
  llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, "lt_debug_print_i8", *module);

  fn_type = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), llvm::ArrayRef<llvm::Type*>{llvm::Type::getInt32Ty(ctx)}, false);
  llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, "lt_debug_print_i32", *module);

  fn_type = llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), llvm::ArrayRef<llvm::Type*>{llvm::Type::getInt64Ty(ctx)}, false);
  llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, "lt_debug_print_i64", *module);
}