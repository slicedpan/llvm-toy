#ifndef SRC_AST_NODE_HPP
#define SRC_AST_NODE_HPP

#include "token.hpp"

namespace LLVMToy {
  class ASTVisitor;

  class ASTNode {
    public:
      ASTNode(const Token& token) {
        this->token = token;
      }
      virtual void accept(ASTVisitor& v) {};
      const Token& get_token() {
        return token;
      }
    private:
      Token token;

  };
}

#endif