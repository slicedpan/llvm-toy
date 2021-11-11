#ifndef FLOATING_POINT_LITERAL_HPP
#define FLOATING_POINT_LITERAL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class FloatingPointLiteral : public Expression {
    public:
      FloatingPointLiteral(const Token& value) {
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