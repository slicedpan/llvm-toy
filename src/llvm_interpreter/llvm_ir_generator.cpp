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

namespace LLVMToy {
  LLVMIRGenerator::LLVMIRGenerator() : 
    value_ref(value_index, 1),
    type_ref(type_index, 1),
    llvm_context(new llvm::LLVMContext()),
    ir_builder(new llvm::IRBuilder<>(*llvm_context))
  {
    root_scope = new Scope();
    current_scope = root_scope;
    cout << "current_scope: " << current_scope << "\n";
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    llvm::Type* struct_element_types[5];
    struct_element_types[0] = llvm::IntegerType::getInt8Ty(*llvm_context);
    struct_element_types[1] = llvm::IntegerType::getInt8Ty(*llvm_context);
    struct_element_types[2] = llvm::IntegerType::getInt16Ty(*llvm_context);   
    struct_element_types[3] = llvm::IntegerType::getInt32Ty(*llvm_context);
    struct_element_types[4] = llvm::IntegerType::getInt64Ty(*llvm_context);
    toy_value_type = llvm::StructType::create(
      *llvm_context,
      llvm::ArrayRef<llvm::Type*>(struct_element_types, 5),
      "lt_struct_type",
      true
    );
    LLVMBuiltins::add_builtins(llvm_module, toy_value_type);
    register_debug_functions(llvm_module);
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
    Value scope_as_val = Value::make_native_ptr((void*)current_scope);
    cout << "csv: current_scope: " << scope_as_val.bindump() << endl;
    return create_lt_value(scope_as_val);
  }

  llvm::Value* LLVMIRGenerator::create_lt_value(Value v) {
    llvm::Value* value_intermediate = ir_builder->CreateInsertValue(
      llvm::UndefValue::get(toy_value_type), 
      llvm::ConstantInt::get(llvm::Type::getInt8Ty(*llvm_context), llvm::APInt(8, (uint8_t)v.type)),
      type_ref
    );

    llvm::Value* result_as_int = llvm::ConstantInt::get(
      llvm::Type::getInt64Ty(*llvm_context),
      llvm::APInt(64, v.int_value)
    );

    return ir_builder->CreateInsertValue(
      value_intermediate,
      result_as_int,
      value_ref
    );
  }

  llvm::Value* LLVMIRGenerator::create_lt_value(int8_t type, llvm::Value* val_as_int64) {
    llvm::Value* value_intermediate = ir_builder->CreateInsertValue(
      llvm::UndefValue::get(toy_value_type), 
      llvm::ConstantInt::get(llvm::Type::getInt8Ty(*llvm_context), llvm::APInt(8, (uint8_t)type)),
      type_ref
    );

    return ir_builder->CreateInsertValue(
      value_intermediate,
      val_as_int64,
      value_ref
    );
  }

  llvm::Module* LLVMIRGenerator::get_module() {
    return llvm_module;
  }

  void LLVMIRGenerator::reset_module() {
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
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
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_puts3");
    assert(fn && "lt_builtin_set_var not found");
    llvm::Value* name_val = create_lt_value(Value::make_string(ref->name.content));
    ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{create_scope_value(), name_val, right});
  }

  void LLVMIRGenerator::visitBinaryOperator(BinaryOperator* binary_operator) {
    llvm::Value* left = gather_value(binary_operator->left);    
    llvm::Value* right = gather_value(binary_operator->right);
    Value op_as_value;
    op_as_value.type = ValueType::Integer;
    op_as_value.int_value = (int64_t)binary_operator->op;
    llvm::Value* op = create_lt_value(op_as_value);

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
    push_value(create_lt_value(Value::make_float(fp_val)));
  }

  void LLVMIRGenerator::visitFunctionCall(FunctionCall* function_call) {
    vector<llvm::Value*> arguments;
    for (int i = 0; i < function_call->arguments.size(); ++i) {
      arguments.push_back(gather_value(function_call->arguments[i]));
    }
    llvm::Value* callee = gather_value(function_call->function);
    // TODO write branching that checks to see what type of function this is
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_puts");
    assert(fn && "lt_builtin_puts not found");
    push_value(ir_builder->CreateCall(fn, arguments));
  }

  void LLVMIRGenerator::visitFunctionDeclaration(FunctionDeclaration* function_declaration) {
    llvm::Function* outer_function = ir_builder->GetInsertBlock()->getParent();
    vector<llvm::Type*> arg_types;
    for (int i = 0; i < function_declaration->arguments.size(); ++i) {
      arg_types.push_back(toy_value_type);
    }
    stringstream ss;

    ss << "fn" << (rand() % 90000) + 10000;

    llvm::FunctionType* fn_type = llvm::FunctionType::get(toy_value_type, arg_types, false);
    llvm::Function* fn = llvm::Function::Create(fn_type, llvm::Function::ExternalLinkage, ss.str(), *llvm_module);

    llvm::Value* fn_ptr_as_int = ir_builder->CreateBitCast(fn, llvm::Type::getInt64Ty(*llvm_context));    

    llvm::BasicBlock* body_block = llvm::BasicBlock::Create(*llvm_context, "", fn);
    ir_builder->SetInsertPoint(body_block);
    for (int i = 0; i < function_declaration->body.size(); ++i) {
      function_declaration->body[i]->accept(*this);
    }
    ir_builder->SetInsertPoint(body_block);
    ir_builder->CreateRet(create_lt_value(Value::make_nil()));
    ir_builder->SetInsertPoint(&outer_function->back());
    push_value(create_lt_value((int8_t)ValueType::Function, fn_ptr_as_int));
  }

  void LLVMIRGenerator::visitIfStatement(IfStatement* if_statement) {
    llvm::Value* condition = gather_value(if_statement->condition);
    llvm::Function* truthiness = llvm_module->getFunction("lt_builtin_truthy");
    llvm::Value* condition_truthy = ir_builder->CreateCall(
      truthiness,
      llvm::ArrayRef<llvm::Value*>{condition}
    );
    llvm::Value* extracted_value = ir_builder->CreateExtractValue(
      condition_truthy,
      llvm::ArrayRef<unsigned int>{1}
    );
    llvm::Value* boolean = ir_builder->CreateBitCast(
      extracted_value,
      llvm::Type::getInt1Ty(*llvm_context)
    );
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
    int64_t int_val = atol(integer_literal->value.content.c_str());
    push_value(create_lt_value(Value::make_int(int_val)));
  }

  void LLVMIRGenerator::visitReturnStatement(ReturnStatement*) {

  }

  void LLVMIRGenerator::visitStringLiteral(StringLiteral* string_literal) {
    push_value(create_lt_value(Value::make_string(string_literal->value.content)));
  }

  void LLVMIRGenerator::visitUnaryOperator(UnaryOperator* unary_operator) {
    llvm::Value* operand = gather_value(unary_operator->expression);
    llvm::Value* op_val = create_lt_value(Value::make_int((int64_t)unary_operator->op));
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_unop");
    assert(fn && "lt_builtin_unop not found");
    push_value(ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{op_val, operand}));
  }

  void LLVMIRGenerator::visitVariableDeclaration(VariableDeclaration* variable_declaration) {

  }

  void LLVMIRGenerator::visitVariableReference(VariableReference* variable_reference) {
    if (variable_reference->name.content == "puts") {
      push_value(create_lt_value(Value::make_builtin_fn(variable_reference->name.content.c_str())));
    } else {
      llvm::Value* name_val = create_lt_value(Value::make_string(variable_reference->name.content));
      llvm::Function* fn = llvm_module->getFunction("lt_builtin_puts2");
      assert(fn && "lt_builtin_get_var not found");
      push_value(
        ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{create_scope_value(), name_val})
      );
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