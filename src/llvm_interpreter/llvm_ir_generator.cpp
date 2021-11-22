#include "llvm_ir_generator.hpp"
#include "llvm_builtins.hpp"
#include "../value.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

namespace LLVMToy {
  LLVMIRGenerator::LLVMIRGenerator() : 
    value_ref(value_index, 1),
    type_ref(type_index, 1),
    llvm_context(new llvm::LLVMContext()),
    ir_builder(new llvm::IRBuilder<>(*llvm_context))
  {
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    llvm::Type* struct_element_types[2];
    struct_element_types[0] = llvm::IntegerType::getInt8Ty(*llvm_context);
    struct_element_types[1] = llvm::IntegerType::getInt64Ty(*llvm_context);
    toy_value_type = llvm::StructType::create(
      *llvm_context,
      llvm::ArrayRef<llvm::Type*>(struct_element_types, 2),
      "lt_struct_type",
      true
    );
    LLVMBuiltins::add_builtins(llvm_module, toy_value_type);
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

    return ir_builder->CreateInsertValue(value_intermediate,
      result_as_int,
      value_ref
    );
  }

  llvm::Module* LLVMIRGenerator::get_module() {
    return llvm_module;
  }

  void LLVMIRGenerator::reset_module() {
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    LLVMBuiltins::add_builtins(llvm_module, toy_value_type);
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

  void LLVMIRGenerator::visitAssignment(Assignment*) {
    
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
    //llvm::Value* callee = gather_value(function_call->function);
    // TODO write branching that checks to see what type of function this is
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_puts");
    assert(fn && "lt_builtin_puts not found");
    push_value(ir_builder->CreateCall(fn, arguments));
  }

  void LLVMIRGenerator::visitFunctionDeclaration(FunctionDeclaration*) {

  }

  void LLVMIRGenerator::visitIfStatement(IfStatement* if_statement) {
    llvm::Value* condition = gather_value(if_statement->condition);
    llvm::Function* truthiness = llvm_module->getFunction("lt_builtin_truthy");
    llvm::Value* condition_truthy = ir_builder->CreateCall(
      truthiness,
      llvm::ArrayRef<llvm::Value*>{condition}
    );
    llvm::Value* boolean = ir_builder->CreateBitCast(
      ir_builder->CreateExtractValue(
        condition_truthy,
        llvm::ArrayRef<unsigned int>{1}
      ),
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
    visitStatements(if_statement->body);
    ir_builder->CreateBr(continue_block);

    // visiting the body could change the current block for ir_builder
    then_block = ir_builder->GetInsertBlock();

    // now link the else block in
    outer_function->getBasicBlockList().push_back(else_block);
    ir_builder->SetInsertPoint(else_block);
    visitStatements(if_statement->else_branch);
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

  void LLVMIRGenerator::visitStringLiteral(StringLiteral*) {

  }

  void LLVMIRGenerator::visitUnaryOperator(UnaryOperator* unary_operator) {
    llvm::Value* operand = gather_value(unary_operator->expression);
    llvm::Value* op_val = create_lt_value(Value::make_int((int64_t)unary_operator->op));
    llvm::Function* fn = llvm_module->getFunction("lt_builtin_unop");
    assert(fn && "lt_builtin_unop not found");
    push_value(ir_builder->CreateCall(fn, llvm::ArrayRef<llvm::Value*>{op_val, operand}));
  }

  void LLVMIRGenerator::visitVariableDeclaration(VariableDeclaration*) {

  }

  void LLVMIRGenerator::visitVariableReference(VariableReference* variable_reference) {
    if (variable_reference->name.content == "puts") {
      push_value(create_lt_value(Value::make_builtin_fn(variable_reference->name.content.c_str())));
    } else {
      push_value(create_lt_value(Value::make_undefined()));
    }
  }

  void LLVMIRGenerator::visitStatements(const vector<Statement*>& statements) {
    llvm::FunctionType* test_fn_type = llvm::FunctionType::get(
      llvm::Type::getDoubleTy(*llvm_context),
      llvm::None,
      false
    );
    llvm::Function* test_fn = llvm::Function::Create(
      test_fn_type,
      llvm::Function::ExternalLinkage,
      "test_fn",
      *llvm_module
    );
    llvm::BasicBlock* test_block = llvm::BasicBlock::Create(*llvm_context, "", test_fn);
    ir_builder->SetInsertPoint(test_block);    
    ir_builder->CreateRet(llvm::ConstantFP::get(*llvm_context, llvm::APFloat(0.42)));

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