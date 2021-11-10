#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class IfStatement : public ASTNode {
    public:
      IfStatement(Expression condition, std::vector<Statement> body, std::vector<Statement> else_branch) {
        
        this->condition = condition;
        
        this->body = body;
        
        this->else_branch = else_branch;
        
      }
    private:
      
      Expression condition;
      
      std::vector<Statement> body;
      
      std::vector<Statement> else_branch;
      
  };
}

#endif