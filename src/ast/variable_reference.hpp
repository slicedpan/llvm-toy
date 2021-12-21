#ifndef VARIABLE_REFERENCE_HPP
#define VARIABLE_REFERENCE_HPP

#include "../token.hpp"
#include "../expression.hpp"
#include <vector>

namespace LLVMToy {
  class VariableReference : public Expression {
    public:
      VariableReference(const Token& token) : Expression(token) {        
        this->name = token.content;
        this->is_closure = false;
      }
      bool assignable() { return true; }
      void accept(ASTVisitor& v);
      bool is_closure;
      string name;
  };
}

#endif