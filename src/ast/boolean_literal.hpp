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
      void debug_print(int indent) {
        tab(indent);
        printf("%s\n", value.content.c_str());
      }
    private:      
      Token value;
  };
}

#endif