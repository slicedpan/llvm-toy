#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "ast_node.hpp"

namespace LLVMToy {
  class Expression : public ASTNode {
    public:
      Expression(const Token& token) : ASTNode(token) {};
      virtual void debug_print(int indent);
      virtual bool assignable() { return false; }
      virtual void accept(ASTVisitor& v) {};
    protected:
      void tab(int indent);      
  };
}
#endif