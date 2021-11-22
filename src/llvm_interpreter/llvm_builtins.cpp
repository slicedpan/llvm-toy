#include "llvm_builtins.hpp"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "../namespace.hpp"
#include "../value.hpp"
#include "../memory_allocation.hpp"
#include "../operator_types.hpp"
#include "../interpreter/operator_action.hpp"

LLVMToy::Value lt_builtin_puts(LLVMToy::Value arg) {
  std::cout << arg.to_string() << std::endl;
  return LLVMToy::Value::make_nil();
}

LLVMToy::Value lt_builtin_binop(LLVMToy::Value op, LLVMToy::Value left, LLVMToy::Value right) {
  LLVMToy::Types::Operator op_type = (LLVMToy::Types::Operator)op.int_value;
  return LLVMToy::OperatorAction::apply_binary_operator(op_type, left, right);
}

LLVMToy::Value lt_builtin_unop(LLVMToy::Value op, LLVMToy::Value operand) {
  LLVMToy::Types::Operator op_type = (LLVMToy::Types::Operator)op.int_value;
  return LLVMToy::OperatorAction::apply_unary_operator(op_type, operand);
}

LLVMToy::Value lt_builtin_truthy(LLVMToy::Value value) {
  return LLVMToy::Value::make_bool(value.is_truthy());
}

namespace LLVMToy {

  void add_builtin(llvm::Module* module, llvm::Type* toy_struct_type, string name, int arity) {
    llvm::Type* types[arity];
    for (int i = 0; i < arity; ++i) {
      types[i] = toy_struct_type;
    }
    llvm::FunctionType* fn_type = llvm::FunctionType::get(toy_struct_type, llvm::ArrayRef<llvm::Type*>(types, arity), false);
    llvm::Function* fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, name, *module);
  }

  void LLVMBuiltins::add_builtins(llvm::Module* module, llvm::Type* toy_struct_type) {
    add_builtin(module, toy_struct_type, "lt_builtin_puts", 1);
    add_builtin(module, toy_struct_type, "lt_builtin_binop", 3);
    add_builtin(module, toy_struct_type, "lt_builtin_unop", 2);
    add_builtin(module, toy_struct_type, "lt_builtin_truthy", 1);

    vector<unsigned int> type_ref{0};
    vector<unsigned int> value_ref{1};

    char* test_string = (char*)allocate(sizeof(char) * 64);
    strcpy(test_string, "JITted code\n");
    llvm::LLVMContext& ctx = module->getContext();
    llvm::IRBuilder<>* builder = new llvm::IRBuilder<>(ctx);

    llvm::Function* fn = module->getFunction("lt_builtin_puts");

    assert(fn != nullptr);

    llvm::Value* value_intermediate = builder->CreateInsertValue(
      llvm::UndefValue::get(toy_struct_type), 
      llvm::ConstantInt::get(llvm::Type::getInt8Ty(ctx), llvm::APInt(8, (int)ValueType::FloatingPoint)),
      type_ref
    );

    double fp_val = 0.5;

    llvm::Value* ptr_as_int = llvm::ConstantInt::get(llvm::Type::getInt64Ty(ctx), *((int64_t*)&fp_val));

    llvm::FunctionType* test_fn_type = llvm::FunctionType::get(
      llvm::Type::getDoubleTy(ctx),
      llvm::None,
      false
    );
    llvm::Function* test_fn = llvm::Function::Create(
      test_fn_type,
      llvm::Function::ExternalLinkage,
      "lt_struct_test_fn",
      *module
    );
    llvm::BasicBlock* test_block = llvm::BasicBlock::Create(ctx, "", test_fn);
    builder->SetInsertPoint(test_block);

    llvm::Value* value = builder->CreateInsertValue(value_intermediate,
      ptr_as_int,
      value_ref
    );
    vector<llvm::Value*> args;
    args.push_back(value);
    builder->CreateCall(fn, args);
    builder->CreateRet(llvm::ConstantFP::get(ctx, llvm::APFloat(1.0)));
  }
}