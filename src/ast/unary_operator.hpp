#ifndef UNARY_OPERATOR_HPP
#define UNARY_OPERATOR_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class UnaryOperator : public Expression {
    public:
      UnaryOperator(const Token& op, Expression* expression) : Expression(op) {
        this->op = Types::TokenToOperator.at(op.type);
        this->expression = expression;
      }
      void accept(ASTVisitor& v);

      Types::Operator op;
      Expression* expression;
  };
}

#endif