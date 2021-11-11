#ifndef VARIABLE_REFERENCE_HPP
#define VARIABLE_REFERENCE_HPP

#include "../token.hpp"
#include "../expression.hpp"
#include <vector>

namespace LLVMToy {
  class VariableReference : public Expression {
    public:
      VariableReference(const Token& name) {        
        this->name = name;
      }
      bool assignable() { return true; }
      void debug_print(int indent) {
        tab(indent);
        printf("VAR_REF(%s)\n", name.content.c_str());
      }
    private:      
      Token name;
  };
}

#endif