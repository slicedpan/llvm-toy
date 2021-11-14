#include "../ast_visitor.hpp"

namespace LLVMToy {
  void Assignment::accept(ASTVisitor& v) {
    v.visitAssignment(this);
  }

  void BinaryOperator::accept(ASTVisitor& v) {
    v.visitBinaryOperator(this);
  }

  void BooleanLiteral::accept(ASTVisitor& v) {
    v.visitBooleanLiteral(this);
  }

  void ExpressionStatement::accept(ASTVisitor& v) {
    v.visitExpressionStatement(this);
  }

  void FloatingPointLiteral::accept(ASTVisitor& v) {
    v.visitFloatingPointLiteral(this);
  }

  void FunctionCall::accept(ASTVisitor& v) {
    v.visitFunctionCall(this);
  }

  void FunctionDeclaration::accept(ASTVisitor& v) {
    v.visitFunctionDeclaration(this);
  }

  void IfStatement::accept(ASTVisitor& v) {
    v.visitIfStatement(this);
  }

  void IntegerLiteral::accept(ASTVisitor& v) {
    v.visitIntegerLiteral(this);
  }

  void ReturnStatement::accept(ASTVisitor &v) {
    v.visitReturnStatement(this);
  }

  void StringLiteral::accept(ASTVisitor& v) {
    v.visitStringLiteral(this);
  }

  void UnaryOperator::accept(ASTVisitor& v) {
    v.visitUnaryOperator(this);
  }

  void VariableDeclaration::accept(ASTVisitor& v) {
    v.visitVariableDeclaration(this);
  }

  void VariableReference::accept(ASTVisitor& v) {
    v.visitVariableReference(this);
  }
}