#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "ast_visitor.hpp"

namespace LLVMToy {
  class ASTPrinter : public ASTVisitor {
    public:
      ASTPrinter();
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
      void print(const vector<Statement*>&);
    private:
      std::vector<string> string_stack;
      string pad(const string&);
      string pop_string();
      void push_string(const string&);
      string gather_outputs(const vector<Statement*>&);
      string gather_outputs(const vector<Expression*>&);
      string gather_output(Statement*);
      string gather_output(Expression*);
  };
}

#endif