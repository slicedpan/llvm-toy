#ifndef LLVM_SCOPE_HPP
#define LLVM_SCOPE_HPP

#include "../namespace.hpp"

namespace llvm {
  class Value;
}

namespace LLVMToy {
  class LLVMScope {
    public:
      LLVMScope(LLVMScope* parent) {
        this->parent = parent;
      }
      LLVMScope() : LLVMScope(nullptr) {}
      LLVMScope* create_child() {
        return new LLVMScope(this);
      }
      llvm::Value* lookup_value(string name) {
        if (variables.count(name) > 0) {
          return variables[name];
        }
        if (parent) {
          return parent->lookup_value(name);
        } else {
          return nullptr;
        }
      }
      void set_value(string name, llvm::Value* value) {
        variables[name] = value;
      }
      LLVMScope* parent;
    private:
      map<string, llvm::Value*> variables;
  };
}

#endif