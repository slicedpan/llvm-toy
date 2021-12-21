#ifndef EXPRESSION_STATEMENT_HPP
#define EXPRESSION_STATEMENT_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class ExpressionStatement : public Statement {
    public:
      ExpressionStatement(const Token& token, Expression* expression) : expression(expression), Statement(token) {}
      ~ExpressionStatement() {
        delete this->expression;
      }
      void accept(ASTVisitor& v);
 
      Expression* expression;
  };
}

#endif