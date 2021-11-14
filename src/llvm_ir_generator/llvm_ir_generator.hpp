#ifndef LLVM_IR_GENERATOR_HPP
#define LLVM_IR_GENERATOR_HPP

#include "../ast_visitor.hpp"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

namespace LLVMToy {
  class LLVMIRGenerator : public ASTVisitor {
    public:
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
      void visitStatements(const std::vector<Statement*>&);
  };
}
#endif