#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "ast_node.hpp"

namespace LLVMToy {
  class Statement : public ASTNode {
    public:    
      virtual void debug_print(int indent);
      virtual void accept(ASTVisitor& v) {};
    protected:
      void tab(int count);
  };
}

#endif