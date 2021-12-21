#ifndef BOOLEAN_LITERAL_HPP
#define BOOLEAN_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class BooleanLiteral : public Expression {
    public:
      BooleanLiteral(const Token& token, bool value) : Expression(token) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
      bool value;
  };
}

#endif