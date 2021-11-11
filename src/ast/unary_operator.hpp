#ifndef UNARY_OPERATOR_HPP
#define UNARY_OPERATOR_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class UnaryOperator : public Expression {
    public:
      UnaryOperator(const Token& op, Expression* expression) {
        this->op = op;
        this->expression = expression;
      }
      void debug_print(int indent) {
        tab(indent);
        printf("UNARY_OP(%s)\n", op.content.c_str());
        tab(indent);
        printf("expression:\n");
        expression->debug_print(indent + 1);
      }
    private:
      Token op;
      Expression* expression;
  };
}

#endif