#ifndef VARIABLE_DECLARATION_HPP
#define VARIABLE_DECLARATION_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class VariableDeclaration : public Statement {
    public:
      VariableDeclaration(const Token& name, Expression* initializer) : Statement(name) {        
        this->name = name.content;
        this->initializer = initializer;
        this->is_closure = false;
      }
      ~VariableDeclaration() {
        delete initializer;
      }
      void accept(ASTVisitor& v);
      bool is_closure;
      string name;      
      Expression* initializer;      
  };
}

#endif