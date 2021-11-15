#include "llvm_ir_generator.hpp"
#include "../value.hpp"

namespace LLVMToy {
  LLVMIRGenerator::LLVMIRGenerator() {
    llvm_context = new llvm::LLVMContext();
    llvm_module = new llvm::Module("llvmtoy", *llvm_context);
    ir_builder = new llvm::IRBuilder<>(*llvm_context);
    llvm::Type* struct_element_types[2];
    struct_element_types[0] = llvm::IntegerType::getInt8Ty(*llvm_context);
    struct_element_types[1] = llvm::IntegerType::getInt64Ty(*llvm_context);    
    toy_value_type = llvm::StructType::create(
      *llvm_context,
      llvm::ArrayRef<llvm::Type*>(struct_element_types, 2)
    );
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

    push_value(ir_builder->CreateFAdd(left, right, "addtmp"));
  }

  void LLVMIRGenerator::visitBooleanLiteral(BooleanLiteral* boolean_literal) {
    bool value = boolean_literal->value.content == "true";
    llvm::Constant* constants[2];
    constants[0] = llvm::ConstantInt::get(llvm::Type::getInt8Ty(*llvm_context), llvm::APInt(8, (int)ValueType::Boolean));
    constants[1] = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*llvm_context), llvm::APInt(64, 1));
    push_value(llvm::ConstantStruct::get(toy_value_type, llvm::ArrayRef(constants, 2)));
  }

  void LLVMIRGenerator::visitExpressionStatement(ExpressionStatement* expression_statement) {
    expression_statement->expression->accept(*this);
    llvm::Value* value = pop_value();
    value->print(llvm::errs());
  }

  void LLVMIRGenerator::visitFloatingPointLiteral(FloatingPointLiteral* floating_point_literal) {
    double value = atof(floating_point_literal->value.content.c_str());
    uint64_t double_as_int = *((uint64_t*)&value);

    llvm::Constant* constants[2];
    constants[0] = llvm::ConstantInt::get(llvm::Type::getInt8Ty(*llvm_context), llvm::APInt(8, (int)ValueType::FloatingPoint));
    constants[1] = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*llvm_context), llvm::APInt(64, double_as_int));
    push_value(llvm::ConstantStruct::get(toy_value_type, llvm::ArrayRef(constants, 2)));
  }

  void LLVMIRGenerator::visitFunctionCall(FunctionCall*) {

  }

  void LLVMIRGenerator::visitFunctionDeclaration(FunctionDeclaration*) {

  }

  void LLVMIRGenerator::visitIfStatement(IfStatement*) {

  }

  void LLVMIRGenerator::visitIntegerLiteral(IntegerLiteral* integer_literal) {
    int64_t value = atoi(integer_literal->value.content.c_str());
    push_value(llvm::ConstantInt::get(llvm::Type::getInt64Ty(*llvm_context), value));
  }

  void LLVMIRGenerator::visitReturnStatement(ReturnStatement*) {

  }

  void LLVMIRGenerator::visitStringLiteral(StringLiteral*) {

  }

  void LLVMIRGenerator::visitUnaryOperator(UnaryOperator*) {

  }

  void LLVMIRGenerator::visitVariableDeclaration(VariableDeclaration*) {

  }

  void LLVMIRGenerator::visitVariableReference(VariableReference*) {

  }
}