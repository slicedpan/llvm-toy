#ifndef BOOLEAN_LITERAL_HPP
#define BOOLEAN_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class BooleanLiteral : public Expression {
    public:
      BooleanLiteral(const Token& value) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
     
      Token value;
  };
}

#endif