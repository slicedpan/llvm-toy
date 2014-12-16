#ifndef SRC_INTEGER_LITERAL_NODE_HPP
#define SRC_INTEGER_LITERAL_NODE_HPP

#include "namespace.hpp"

#include "ast_node.hpp"

namespace LLVMToy {
  class IntegerLiteralNode : public ASTNode {
    public:
      IntegerLiteralNode(int64_t v);
      ~IntegerLiteralNode();
    private:
      int64_t value;
  };
}

#endif