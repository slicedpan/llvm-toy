#ifndef STRING_LITERAL_HPP
#define STRING_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class StringLiteral : public Expression {
    public:
      StringLiteral(const Token& value) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
    
      Token value;
  };
}

#endif