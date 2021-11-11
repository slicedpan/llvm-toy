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
      ExpressionStatement(Expression* expression) : expression(expression) {}
      ~ExpressionStatement() {
        delete this->expression;
      }
      void debug_print(int indent) {
        tab(indent);
        printf("EXPR_STMT\n");
        tab(indent);
        printf("expression:\n");
        expression->debug_print(indent + 1);
      }
    private:      
      Expression* expression;
  };
}

#endif