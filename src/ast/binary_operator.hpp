#ifndef BINARY_OPERATOR_HPP
#define BINARY_OPERATOR_HPP

#include "../token.hpp"
#include "../expression.hpp"
#include "../operator_types.hpp"

namespace LLVMToy {
  class BinaryOperator : public Expression {
    public:
      BinaryOperator(const Token& op, Expression* left, Expression* right) : Expression(op) {        
        this->left = left;
        this->right = right;
        this->op = Types::TokenToOperator.at(op.type);
      }
      void accept(ASTVisitor& v);

      Expression* left;
      Expression* right;
      Types::Operator op;
  };
}

#endif