#ifndef FUNCTION_DECLARATION_HPP
#define FUNCTION_DECLARATION_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class FunctionDeclaration : public Expression {
    public:
      FunctionDeclaration(const std::vector<Token>& arguments, std::vector<Statement*> body) {        
        this->arguments = arguments;
        this->body = body;
      }
      ~FunctionDeclaration() {
        for (auto iter = body.begin(); iter != body.end(); ++iter) {
          delete *iter;
        }
      }
      
      void accept(ASTVisitor& v);
    
      std::vector<Token> arguments;
      std::vector<Statement*> body;
  };
}

#endif