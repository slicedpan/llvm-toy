#ifndef LEXICAL_SCOPE_HPP
#define LEXICAL_SCOPE_HPP

#include "namespace.hpp"

namespace LLVMToy {
  class VariableDeclaration;

  class LexicalScope {
    public:
      struct LookupResult {
        int offset;
        VariableDeclaration* declaration;
      };
      LexicalScope(LexicalScope* parent) {
        this->parent = parent;
      }
      LexicalScope() : LexicalScope(nullptr) {}
      inline void add_declaration(string name, VariableDeclaration* var_ref) {
        declarations[name] = var_ref;
      }
      inline LookupResult find_var(string name, int offset) {
        LookupResult lr;
        lr.offset = offset;
        if (var_is_local(name)) {
          lr.declaration = declarations[name];
          return lr;
        }
        if (parent == nullptr) {
          lr.declaration = nullptr;
          return lr;
        } else {
          return parent->find_var(name, offset + 1);
        }
      }
      inline LookupResult find_var(string name) {
        return find_var(name, 0);
      }
      inline bool var_is_local(string name) {
        return declarations.count(name) > 0;
      }
      inline LexicalScope* create_child() {
        return new LexicalScope(this);
      }
    private:
      LexicalScope* parent;
      map<string, VariableDeclaration*> declarations;
  };
}

#endif