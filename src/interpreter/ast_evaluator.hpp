#ifndef AST_EVALUATOR_HPP
#define AST_EVALUATOR_HPP

#include "../ast_visitor.hpp"
#include "../ast_node.hpp"
#include "scope.hpp"

namespace LLVMToy {
  class ASTEvaluator : public ASTVisitor {
    public:
      ASTEvaluator() : return_flag(false) {};
      void visitAssignment(Assignment*);
      void visitBinaryOperator(BinaryOperator*);
      void visitBooleanLiteral(BooleanLiteral*);
      void visitExpressionStatement(ExpressionStatement*);
      void visitFloatingPointLiteral(FloatingPointLiteral*);
      void visitFunctionCall(FunctionCall*);
      void visitFunctionExpression(FunctionExpression*);
      void visitIfStatement(IfStatement*);
      void visitIntegerLiteral(IntegerLiteral*);
      void visitReturnStatement(ReturnStatement*);
      void visitStringLiteral(StringLiteral*);
      void visitUnaryOperator(UnaryOperator*);
      void visitVariableDeclaration(VariableDeclaration*);
      void visitVariableReference(VariableReference*);
      void evaluate(vector<Statement*>, Scope*);
      Value get_return_value();
    private:
      Value pop_value();
      void push_value(Value);
      Scope* current_scope;
      vector<Value> value_stack;
      const Value nil_value{ ValueType::Nil };
      Value gather_value(ASTNode*);
      bool return_flag;
  };
}

#endif