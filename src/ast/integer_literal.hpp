#ifndef INTEGER_LITERAL_HPP
#define INTEGER_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class IntegerLiteral : public Expression {
    public:
      IntegerLiteral(const Token& value) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
    
      Token value;
  };
}

#endif