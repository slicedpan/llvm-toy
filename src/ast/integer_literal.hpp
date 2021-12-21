#ifndef INTEGER_LITERAL_HPP
#define INTEGER_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class IntegerLiteral : public Expression {
    public:
      IntegerLiteral(const Token& token, int value) : Expression(token) {
        this->value = value;
      }
      void accept(ASTVisitor& v);
      int value;
  };
}

#endif