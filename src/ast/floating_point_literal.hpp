#ifndef FLOATING_POINT_LITERAL_HPP
#define FLOATING_POINT_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class FloatingPointLiteral : public Expression {
    public:
      FloatingPointLiteral(const Token& token, double value) : Expression(token) {
        this->value = value;
      }
      void accept(ASTVisitor& v);  
      double value;
  };
}

#endif