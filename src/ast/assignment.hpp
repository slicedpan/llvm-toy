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
      void accept(ASTVisitor& v);

      Expression* left;
      Expression* right;
  };
}

#endif