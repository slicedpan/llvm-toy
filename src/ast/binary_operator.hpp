#ifndef BINARY_OPERATOR_HPP
#define BINARY_OPERATOR_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class BinaryOperator : public Expression {
    public:
      BinaryOperator(const Token& op, Expression* left, Expression* right) {
        this->op = op;
        this->left = left;
        this->right = right;
      }
      void debug_print(int indent) {
        tab(indent);
        printf("BINARY_OP(%s)\n",op.content.c_str());
        tab(indent);
        printf("left:\n");
        left->debug_print(indent + 1);
        tab(indent);
        printf("right:\n");
        right->debug_print(indent + 1);
      }
    private:
      Token op;
      Expression* left;
      Expression* right;
  };
}

#endif