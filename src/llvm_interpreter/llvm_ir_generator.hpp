#ifndef LLVM_IR_GENERATOR_HPP
#define LLVM_IR_GENERATOR_HPP

#include "../ast_visitor.hpp"
#include "../value.hpp"
#include "llvm/IR/IRBuilder.h"

namespace llvm {
  class LLVMContext;
  class StructType;
  class Module;
  template<typename> class ArrayRef;
}

namespace LLVMToy {
  class Scope;

  class LLVMIRGenerator : public ASTVisitor {
    public:
      LLVMIRGenerator();
      void visitAssignment(Assignment*);
      void visitBinaryOperator(BinaryOperator*);
      void visitBooleanLiteral(BooleanLiteral*);
      void visitExpressionStatement(ExpressionStatement*);
      void visitFloatingPointLiteral(FloatingPointLiteral*);
      void visitFunctionCall(FunctionCall*);
      void visitFunctionDeclaration(FunctionDeclaration*);
      void visitIfStatement(IfStatement*);
      void visitIntegerLiteral(IntegerLiteral*);
      void visitReturnStatement(ReturnStatement*);
      void visitStringLiteral(StringLiteral*);
      void visitUnaryOperator(UnaryOperator*);
      void visitVariableDeclaration(VariableDeclaration*);
      void visitVariableReference(VariableReference*);
      void visitStatements(const vector<Statement*>&);
      
      llvm::Value* create_lt_value(Value);
      llvm::Value* create_lt_value(int8_t, llvm::Value*);
      llvm::Value* create_scope_value();
      void print();
      llvm::Module* get_module();
      void reset_module();
    private:
      llvm::Value* create_pointer_value(uint8_t, llvm::Value*);
      llvm::Type* toy_value_type;
      llvm::Value* gather_value(ASTNode*);
      llvm::Value* pop_value();      
      void push_value(llvm::Value*);
      void print_lt_value(llvm::Value*);
      void print_llvm_value(llvm::Value*);
      vector<llvm::Value*> value_stack;
      llvm::LLVMContext* llvm_context;
      llvm::Module* llvm_module;
      llvm::IRBuilder<>* ir_builder;
      unsigned int type_index[1] = {0};
      unsigned int value_index[1] = {2};
      llvm::ArrayRef<unsigned int> type_ref;
      llvm::ArrayRef<unsigned int> value_ref;
      Scope* root_scope;
      Scope* current_scope;
  };
}
#endif