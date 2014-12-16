#ifndef SRC_ABSTRACT_SYNTAX_TREE_H
#define SRC_ABSTRACT_SYNTAX_TREE_H

#include "namespace.hpp"
#include <memory>

namespace LLVMToy {

  class ASTNode;

  class AbstractSyntaxTree {
    public:
      void AddNode(shared_ptr<ASTNode> node);
    private:
      vector<shared_ptr<ASTNode> > nodes;
  };
}

#endif