#ifndef FUNCTION_CALL_HPP
#define FUNCTION_CALL_HPP

#include "../token.hpp"
#include "../expression.hpp"

namespace LLVMToy {
  class FunctionCall : public Expression {
    public:
      FunctionCall(Expression* function, std::vector<Expression*> arguments) {
        this->function = function;
        this->arguments = arguments;
      }
      void accept(ASTVisitor& v);

      Expression* function;
      std::vector<Expression*> arguments;
  };
}

#endif