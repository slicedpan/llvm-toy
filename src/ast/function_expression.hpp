#ifndef FUNCTION_EXPRESSION_HPP
#define FUNCTION_EXPRESSION_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class FunctionExpression : public Expression {
    public:
      FunctionExpression(const Token& token, const std::vector<Token>& arguments, std::vector<Statement*> body, string name) : Expression(token){
        this->arguments = arguments;
        this->body = body;
        this->name = name;
      }
      ~FunctionExpression() {
        for (auto iter = body.begin(); iter != body.end(); ++iter) {
          delete *iter;
        }
      }
      
      void accept(ASTVisitor& v);
      string name;
      std::vector<Token> arguments;
      std::vector<Statement*> body;
  };
}

#endif