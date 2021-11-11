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
      void debug_print(int indent) {
        tab(indent);
        printf("%s\n", value.content.c_str());
      }
    private:      
      Token value;
  };
}

#endif