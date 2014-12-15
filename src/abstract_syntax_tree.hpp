#ifndef SRC_ABSTRACT_SYNTAX_TREE_H
#define SRC_ABSTRACT_SYNTAX_TREE_H

namespace LLVMToy {

  class ASTNode;

  class AbstractSyntaxTree {
    void AddNode(ASTNode& node);
  };
}

#endif