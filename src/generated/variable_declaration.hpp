#ifndef VARIABLE_DECLARATION_HPP
#define VARIABLE_DECLARATION_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class VariableDeclaration : public ASTNode {
    public:
      VariableDeclaration(Token name, Expression initializer) {
        
        this->name = name;
        
        this->initializer = initializer;
        
      }
    private:
      
      Token name;
      
      Expression initializer;
      
  };
}

#endif