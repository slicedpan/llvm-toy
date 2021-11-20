#include "llvm_builtins.hpp"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "../namespace.hpp"
#include "../value.hpp"
#include "../memory_allocation.hpp"

LLVMToy::Value lt_builtin_puts(LLVMToy::Value arg) {
  std::cout << arg.to_string() << std::endl;
  return LLVMToy::Value::make_nil();
}

namespace LLVMToy {

  llvm::StructType* create_toy_struct_type(llvm::Module* module) {
    llvm::Type* struct_element_types[2];
    struct_element_types[0] = llvm::IntegerType::getInt8Ty(module->getContext());
    struct_element_types[1] = llvm::IntegerType::getInt64Ty(module->getContext());    
    return llvm::StructType::create(
      module->getContext(),
      llvm::ArrayRef<llvm::Type*>(struct_element_types, 2)
    );    
  }

  void add_builtin(llvm::Module* module, string name, int arity) {
    llvm::StructType* toy_struct_type = create_toy_struct_type(module);
    llvm::Type* types[arity];
    for (int i = 0; i < arity; ++i) {
      types[i] = toy_struct_type;
    }
    llvm::FunctionType* fn_type = llvm::FunctionType::get(toy_struct_type, llvm::ArrayRef<llvm::Type*>(types, arity), false);
    llvm::Function* fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, name, *module);
  }

  void LLVMBuiltins::add_builtins(llvm::Module* module) {
    add_builtin(module, "lt_builtin_puts", 1);

    vector<unsigned int> type_ref{0};
    vector<unsigned int> value_ref{1};

    char* test_string = (char*)allocate(sizeof(char) * 64);
    strcpy(test_string, "JITted code\n");
    llvm::LLVMContext& ctx = module->getContext();
    llvm::IRBuilder<>* builder = new llvm::IRBuilder<>(ctx);

    llvm::StructType* toy_struct_type = create_toy_struct_type(module);
    llvm::Function* fn = module->getFunction("lt_builtin_puts");

    llvm::Value* value_intermediate = builder->CreateInsertValue(
      llvm::UndefValue::get(toy_struct_type), 
      llvm::ConstantInt::get(llvm::Type::getInt8Ty(ctx), llvm::APInt(8, (int)ValueType::String)),
      type_ref
    );

    llvm::Value* ptr_as_int = llvm::ConstantInt::get(llvm::Type::getInt64Ty(ctx), (int64_t)test_string);

    llvm::Value* value = builder->CreateInsertValue(value_intermediate,
      ptr_as_int,
      value_ref
    );

    vector<llvm::Value*> args{value};

    builder->CreateCall(fn, args);
  }
}