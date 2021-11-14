#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP

#include "../ast_node.hpp"
#include "../token.hpp"
#include "../expression.hpp"
#include "../statement.hpp"
#include <vector>

namespace LLVMToy {
  class ReturnStatement : public Statement {
    public:
      ReturnStatement(Expression* expression) {
        this->expression = expression;
      }
      ~ReturnStatement() {
        delete this->expression;
      }
      void accept(ASTVisitor &v);

      Expression* expression;
  };
}

#endif