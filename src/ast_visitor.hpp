#ifndef AST_VISITOR_HPP
#define AST_VISITOR_HPP

#include "ast/assignment.hpp"
#include "ast/binary_operator.hpp"
#include "ast/boolean_literal.hpp"
#include "ast/expression_statement.hpp"
#include "ast/floating_point_literal.hpp"
#include "ast/function_call.hpp"
#include "ast/function_expression.hpp"
#include "ast/if_statement.hpp"
#include "ast/integer_literal.hpp"
#include "ast/return_statement.hpp"
#include "ast/string_literal.hpp"
#include "ast/unary_operator.hpp"
#include "ast/variable_declaration.hpp"
#include "ast/variable_reference.hpp"

namespace LLVMToy {
  class ASTVisitor {
    public:
      virtual void visitAssignment(Assignment*) {};
      virtual void visitBinaryOperator(BinaryOperator*) {};
      virtual void visitBooleanLiteral(BooleanLiteral*) {};
      virtual void visitExpressionStatement(ExpressionStatement*) {};
      virtual void visitFloatingPointLiteral(FloatingPointLiteral*) {};
      virtual void visitFunctionCall(FunctionCall*) {};
      virtual void visitFunctionExpression(FunctionExpression*) {};
      virtual void visitIfStatement(IfStatement*) {};
      virtual void visitIntegerLiteral(IntegerLiteral*) {};
      virtual void visitReturnStatement(ReturnStatement*) {};
      virtual void visitStringLiteral(StringLiteral*) {};
      virtual void visitUnaryOperator(UnaryOperator*) {};
      virtual void visitVariableDeclaration(VariableDeclaration*) {};
      virtual void visitVariableReference(VariableReference*) {};
      virtual void visitStatements(const std::vector<Statement*>&);
  };
}

#endif