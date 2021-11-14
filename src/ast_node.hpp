#ifndef SRC_AST_NODE_HPP
#define SRC_AST_NODE_HPP

namespace LLVMToy {
  class ASTVisitor;

  class ASTNode {
    public:
      virtual void accept(ASTVisitor& v) {};
  };
}

#endif