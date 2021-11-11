#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class Assignment : public Expression {
    public:
      Assignment(Expression* left, Expression* right) {
        this->left = left;
        this->right = right;
      }
      void debug_print(int indent) {
        tab(indent);
        printf("ASSIGNMENT\n");
        tab(indent);
        printf("left:\n");
        left->debug_print(indent + 1);
        tab(indent);
        printf("right:\n");
        right->debug_print(indent + 1);
      }
    private:
      Expression* left;
      Expression* right;
  };
}

#endif