#include "ast_visitor.hpp"

namespace LLVMToy {
  void ASTVisitor::visitStatements(const std::vector<Statement*>& statements) {
    for (int i = 0; i < statements.size(); ++i) {
      statements[i]->accept(*this);
    }
  }
}