#ifndef STRING_LITERAL_HPP
#define STRING_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class StringLiteral : public Expression {
    public:
      StringLiteral(const Token& token, string value) : Expression(token) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
      string value;
  };
}

#endif