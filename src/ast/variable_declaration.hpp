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
      VariableDeclaration(const Token& name, Expression* initializer) {        
        this->name = name;        
        this->initializer = initializer;        
      }
      ~VariableDeclaration() {
        delete initializer;
      }
      void debug_print(int indent) {
        tab(indent);
        printf("VAR\n");
        tab(indent);
        printf("name: %s\n", this->name.content.c_str());
        if (this->initializer) {
          tab(indent);
          printf("initializer:\n");
          initializer->debug_print(indent + 1);
        }
      }      
    private:      
      Token name;      
      Expression* initializer;      
  };
}

#endif