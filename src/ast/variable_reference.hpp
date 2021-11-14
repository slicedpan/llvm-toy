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
      void accept(ASTVisitor& v);
    
      Token name;
  };
}

#endif