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
#include "../interpreter/scope.hpp"
#include "closure_container.hpp"
#include <cstdint>

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_set_var(LLVMToy::Value scope_as_val, LLVMToy::Value name, LLVMToy::Value value) {
  LLVMToy::Scope* scope = (LLVMToy::Scope*)scope_as_val.pointer_value();
  scope->set_variable(name.to_string(), value);
  return value;
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_get_var(LLVMToy::Value scope_as_val, LLVMToy::Value name) {
  LLVMToy::Scope* scope = (LLVMToy::Scope*)scope_as_val.pointer_value();
  return scope->lookup_variable(name.to_string());
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_puts(LLVMToy::Value arg) {
  std::cout << arg.to_string() << std::endl;
  return LLVMToy::Value::make_nil();
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_puts2(LLVMToy::Value scope_as_val, LLVMToy::Value name) {
  LLVMToy::Scope* scope = (LLVMToy::Scope*)scope_as_val.pointer_value();
  LLVMToy::Value val = scope->lookup_variable(name.to_string());
  return val;
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_puts3(LLVMToy::Value scope_as_val, LLVMToy::Value name, LLVMToy::Value value) {
  LLVMToy::Scope* scope = (LLVMToy::Scope*)scope_as_val.pointer_value();
  scope->set_variable(name.to_string(), value);
  return value;
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_binop(LLVMToy::Value op, LLVMToy::Value left, LLVMToy::Value right) {
  LLVMToy::Types::Operator op_type = (LLVMToy::Types::Operator)op.float_value;
  return LLVMToy::OperatorAction::apply_binary_operator(op_type, left, right);
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_unop(LLVMToy::Value op, LLVMToy::Value operand) {
  LLVMToy::Types::Operator op_type = (LLVMToy::Types::Operator)op.float_value;
  return LLVMToy::OperatorAction::apply_unary_operator(op_type, operand);
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_truthy(LLVMToy::Value value) {
  return LLVMToy::Value::make_bool(value.is_truthy());
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_closure_read(LLVMToy::Value closure_container_ptr, LLVMToy::Value index) {
  LLVMToy::ClosureContainer* container = (LLVMToy::ClosureContainer*)closure_container_ptr.pointer_value();
  return container->get_slot_value((unsigned int)index.float_value);
}

LLVMToy::Value __attribute__((aligned(8))) lt_builtin_closure_write(LLVMToy::Value closure_container_ptr, LLVMToy::Value index, LLVMToy::Value value) {
  LLVMToy::ClosureContainer* container = (LLVMToy::ClosureContainer*)closure_container_ptr.pointer_value();
  container->set_slot_value((unsigned int)index.float_value, value);
  return value;
}

namespace LLVMToy {
  void add_va_builtin(llvm::Module* module, llvm::Type* toy_struct_type, string name) {
    
  }

  void LLVMBuiltins::add_builtin(llvm::Module* module, llvm::Type* toy_struct_type, string name, int arity) {
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
    add_builtin(module, toy_struct_type, "lt_builtin_get_var", 2);
    add_builtin(module, toy_struct_type, "lt_builtin_set_var", 3);
    add_builtin(module, toy_struct_type, "lt_builtin_puts2", 2);
    add_builtin(module, toy_struct_type, "lt_builtin_puts3", 3);
    add_builtin(module, toy_struct_type, "lt_builtin_closure_read", 2);
    add_builtin(module, toy_struct_type, "lt_builtin_closure_write", 3);
  }
}