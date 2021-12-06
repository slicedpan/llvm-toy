#include "llvm_ir_generator.hpp"
#include "llvm_builtins.hpp"
#include "../value.hpp"
#include "debug_printer.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "../interpreter/scope.hpp"
#include "llvm_scope.hpp"

namespace LLVMToy {
  LLVMIRGenerator::LLVMIRGenerator() : 
    value_ref(value_index, 1),
    type_ref(type_index, 1),
    llvm_context(new llvm::LLVMContext()),
    ir_builder(new llvm::IRBuilder<>(*llvm_context))
  {
    root_scope = new LLVMScope();
    current_scope = root_scope;
    cout << "current_scope: " << current_scope << "\n";
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    toy_value_type = llvm::Type::getInt64Ty(*llvm_context);
    true_value = llvm::ConstantInt::getIntegerValue(llvm::Type::getInt64Ty(*llvm_context), llvm::APInt(64, TRUE_VALUE));
    false_value = llvm::ConstantInt::getIntegerValue(llvm::Type::getInt64Ty(*llvm_context), llvm::APInt(64, FALSE_VALUE));
    setup_module();
  }

  void LLVMIRGenerator::print_lt_value(llvm::Value* val) {
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_puts");
    ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{val});
  }

  void LLVMIRGenerator::print_llvm_value(llvm::Value* val) {
    auto type = val->getType();
    string function_name;
    if (type == llvm::Type::getInt1Ty(*llvm_context)) {
      function_name = "lt_debug_print_i1";
    }
    if (type == llvm::Type::getInt8Ty(*llvm_context)) {
      function_name = "lt_debug_print_i8";
    }
    if (type == llvm::Type::getInt32Ty(*llvm_context)) {
      function_name = "lt_debug_print_i32";
    }
    if (type == llvm::Type::getInt64Ty(*llvm_context)) {
      function_name = "lt_debug_print_i64";
    }
    llvm::Function* fn = llvm_module->getFunction(function_name);
    assert(fn && "debug function does not exist");
    ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{val});
  }

  llvm::Value* LLVMIRGenerator::create_scope_value() {
    Value scope_as_val = Value::make_generic_ptr((void*)current_scope);
    cout << "csv: current_scope: " << scope_as_val.bindump() << endl;
    return create_lt_value(scope_as_val);
  }

  llvm::Value* LLVMIRGenerator::create_lt_value(Value v) {
    return llvm::ConstantInt::get(toy_value_type, llvm::APInt(64, v.uint_value));
  }

  llvm::Value* LLVMIRGenerator::create_pointer_value(uint8_t type, llvm::Value* pointer) {
    uint64_t base_value = QNAN | POINTER_BIT;
    switch (type) {
      case ValueType::Function:
        base_value |= FUNCTION_POINTER;        
        break;
      default:
        base_value |= GENERIC_POINTER;
        break;
    }
    llvm::Value* base = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*llvm_context), llvm::APInt(64, base_value));
    llvm::Value* ptr_as_uint64 = ir_builder->CreatePtrToInt(pointer, llvm::Type::getInt64Ty(*llvm_context));
    return ir_builder->CreateOr(base, ptr_as_uint64);
  }

  llvm::Module* LLVMIRGenerator::get_module() {
    return llvm_module;
  }

  void LLVMIRGenerator::reset_module() {
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    setup_module();        
  }

  void LLVMIRGenerator::setup_module() {
    LLVMBuiltins::add_builtins(llvm_module, toy_value_type);
    register_debug_functions(llvm_module);
  }

  llvm::Value* LLVMIRGenerator::pop_value() {
    auto ret = value_stack.back();
    value_stack.pop_back();
    return ret;
  }

  llvm::Value* LLVMIRGenerator::gather_value(ASTNode* node) {
    node->accept(*this);
    return pop_value();
  }

  void LLVMIRGenerator::push_value(llvm::Value* val) {
    value_stack.push_back(val);
  }

  void LLVMIRGenerator::print() {
    llvm_module->print(llvm::errs(), nullptr);
  }

  void LLVMIRGenerator::visitAssignment(Assignment* assignment) {
    llvm::Value* right = gather_value(assignment->right);
    VariableReference* ref = (VariableReference*)assignment->left;
    current_scope->set_value(ref->name.content, right);
  }

  void LLVMIRGenerator::visitBinaryOperator(BinaryOperator* binary_operator) {
    llvm::Value* left = gather_value(binary_operator->left);    
    llvm::Value* right = gather_value(binary_operator->right);
    llvm::Value* op = create_lt_value(Value::make_number((double)(uint32_t)binary_operator->op));

    llvm::Function* fn = llvm_module->getFunction("lt_builtin_binop");
    assert(fn && "lt_builtin_binop not found");
    auto call = ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{op, left, right});    
    
    push_value(call);
  }

  void LLVMIRGenerator::visitBooleanLiteral(BooleanLiteral* boolean_literal) {
    bool value = boolean_literal->value.content == "true";
    push_value(create_lt_value(Value::make_bool(value)));
  }

  void LLVMIRGenerator::visitExpressionStatement(ExpressionStatement* expression_statement) {
    push_value(gather_value(expression_statement->expression));
  }

  void LLVMIRGenerator::visitFloatingPointLiteral(FloatingPointLiteral* floating_point_literal) {
    double fp_val = atof(floating_point_literal->value.content.c_str());
    push_value(create_lt_value(Value::make_number(fp_val)));
  }

  void LLVMIRGenerator::visitFunctionCall(FunctionCall* function_call) {
    vector<llvm::Value*> arguments;
    vector<llvm::Type*> arg_types;
    for (int i = 0; i < function_call->arguments.size(); ++i) {
      arguments.push_back(gather_value(function_call->arguments[i]));
      arg_types.push_back(toy_value_type);
    }
    llvm::Value* callee = gather_value(function_call->function);
    llvm::FunctionType* fn_type = llvm::FunctionType::get(toy_value_type, arg_types, false);
    llvm::Value* unmasked_int = ir_builder->CreateAnd(callee, POINTER_HI_MASK);
    llvm::Value* unmasked_pointer = ir_builder->CreateIntToPtr(
      unmasked_int,
      fn_type->getPointerTo()
    );
    
    push_value(ir_builder->CreateCall(fn_type, unmasked_pointer, arguments));
  }

  void LLVMIRGenerator::visitFunctionDeclaration(FunctionDeclaration* function_declaration) {
    llvm::Function* outer_function = ir_builder->GetInsertBlock()->getParent();
    vector<llvm::Type*> arg_types;
    LLVMScope* last_scope = current_scope;
    current_scope = current_scope->create_child();
    for (int i = 0; i < function_declaration->arguments.size(); ++i) {
      arg_types.push_back(toy_value_type);
    }
    stringstream ss;

    llvm::FunctionType* fn_type = llvm::FunctionType::get(toy_value_type, arg_types, false);
    llvm::Function* fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, "", *llvm_module);

    for (int i = 0; i < function_declaration->arguments.size(); ++i) {
      current_scope->set_value(function_declaration->arguments[i].content, fn->getArg(i));
    }

    llvm::BasicBlock* body_block = llvm::BasicBlock::Create(*llvm_context, "", fn);
    ir_builder->SetInsertPoint(body_block);

    for (int i = 0; i < function_declaration->body.size(); ++i) {
      function_declaration->body[i]->accept(*this);
    }
    
    ir_builder->SetInsertPoint(body_block);
    if (!body_block->getTerminator()) {
      ir_builder->CreateRet(create_lt_value(Value::make_nil()));
    }
    ir_builder->SetInsertPoint(&outer_function->back());
    delete current_scope;
    current_scope = last_scope;
    push_value(create_pointer_value(ValueType::Function, fn));
  }

  void LLVMIRGenerator::visitIfStatement(IfStatement* if_statement) {
    llvm::Value* condition = gather_value(if_statement->condition);
    llvm::Function* truthiness = llvm_module->getFunction("lt_builtin_truthy");
    llvm::Value* condition_truthy = ir_builder->CreateCall(
      truthiness,
      llvm::ArrayRef<llvm::Value*>{condition}
    );
    
    llvm::Value* boolean = ir_builder->CreateICmpEQ(condition_truthy, true_value);
    llvm::Function* outer_function = ir_builder->GetInsertBlock()->getParent();
    // then block is linked to outer function
    llvm::BasicBlock* then_block = llvm::BasicBlock::Create(*llvm_context, "then", outer_function);
    // these blocks are not linked yet, because they need to appear after the instructions in the then block
    llvm::BasicBlock* else_block = llvm::BasicBlock::Create(*llvm_context, "else");
    llvm::BasicBlock* continue_block = llvm::BasicBlock::Create(*llvm_context, "if-cont");

    ir_builder->CreateCondBr(boolean, then_block, else_block);
    ir_builder->SetInsertPoint(then_block);
    for (int i = 0; i < if_statement->body.size(); ++i) {
      if_statement->body[i]->accept(*this);
    }
    ir_builder->CreateBr(continue_block);

    // visiting the body could change the current block for ir_builder
    then_block = ir_builder->GetInsertBlock();

    // now link the else block in
    outer_function->getBasicBlockList().push_back(else_block);
    ir_builder->SetInsertPoint(else_block);
    for (int i = 0; i < if_statement->else_branch.size(); ++i) {
      if_statement->else_branch[i]->accept(*this);
    }
    ir_builder->CreateBr(continue_block);

    // as with then block, the insert point for ir_builder could change
    else_block = ir_builder->GetInsertBlock();

    // now link continuation block and set it as the insert point
    outer_function->getBasicBlockList().push_back(continue_block);
    ir_builder->SetInsertPoint(continue_block);    
  }

  void LLVMIRGenerator::visitIntegerLiteral(IntegerLiteral* integer_literal) {
    push_value(create_lt_value(Value::make_number(atof(integer_literal->value.content.c_str()))));
  }

  void LLVMIRGenerator::visitReturnStatement(ReturnStatement* return_statement) {
    llvm::Value* ret;
    if (return_statement->expression) {
      ret = gather_value(return_statement->expression);
    } else {
      ret = create_lt_value(Value::make_nil());
    }
    ir_builder->CreateRet(ret);
  }

  void LLVMIRGenerator::visitStringLiteral(StringLiteral* string_literal) {
    push_value(create_lt_value(Value::make_string(string_literal->value.content)));
  }

  void LLVMIRGenerator::visitUnaryOperator(UnaryOperator* unary_operator) {
    llvm::Value* operand = gather_value(unary_operator->expression);
    llvm::Value* op_val = create_lt_value(Value::make_number((int32_t)unary_operator->op));
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_unop");
    assert(fn && "lt_builtin_unop not found");
    push_value(ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{op_val, operand}));
  }

  void LLVMIRGenerator::visitVariableDeclaration(VariableDeclaration* variable_declaration) {
    llvm::Value* initial_value;
    if (variable_declaration->initializer) {
      initial_value = gather_value(variable_declaration->initializer);
    } else {
      initial_value = create_lt_value(Value::make_undefined());
    }
    current_scope->set_value(variable_declaration->name.content, initial_value);
  }

  void LLVMIRGenerator::visitVariableReference(VariableReference* variable_reference) {
    if (variable_reference->name.content == "puts") {
      push_value(create_lt_value(Value::make_function_ptr((void*)lt_builtin_puts)));
    } else {
      LLVMScope::LookupResult res = current_scope->lookup_value(variable_reference->name.content);
      if (res.depth != current_scope->depth) {
        
      } else {
        push_value(res.value);
      }      
    }
  }

  void LLVMIRGenerator::visitStatements(const vector<Statement*>& statements) {
    llvm::FunctionType* entry_fn_type = llvm::FunctionType::get(
      llvm::Type::getVoidTy(*llvm_context),
      llvm::None,
      false
    );
    llvm::Function* entry_fn = llvm::Function::Create(
      entry_fn_type,
      llvm::Function::ExternalLinkage,
      "entrypoint_fn",
      *llvm_module
    );
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*llvm_context, "", entry_fn);
    ir_builder->SetInsertPoint(block);
    for (int i = 0; i < statements.size(); ++i) {
      statements[i]->accept(*this);
    }
    ir_builder->CreateRet(nullptr);
  }

}
