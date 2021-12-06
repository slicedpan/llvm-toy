#ifndef LLVM_SCOPE_HPP
#define LLVM_SCOPE_HPP

#include "../namespace.hpp"

namespace llvm {
  class Value;
}

namespace LLVMToy {

  class LLVMScope {
    public:
      struct LookupResult {
        uint16_t depth;
        llvm::Value* value;
        LookupResult(uint16_t depth, llvm::Value* value) : depth(depth), value(value) {}      
      };
      LLVMScope(LLVMScope* parent, uint16_t depth) {
        this->parent = parent;
        this->depth = depth;
        parent->children.push_back(this);
      }
      LLVMScope() : LLVMScope(nullptr, 0) {}
      LLVMScope* create_child() {
        return new LLVMScope(this, depth + 1);
      }
      LookupResult lookup_value(string name) {
        if (variables.count(name) > 0) {
          return LookupResult(depth, variables[name]);
        }
        if (parent) {
          return parent->lookup_value(name);
        } else {
          return LookupResult(depth, nullptr);;
        }
      }
      void set_value(string name, llvm::Value* value) {
        variables[name] = value;
      }
      LLVMScope* parent;
      uint16_t depth;
    private:
      vector<LLVMScope*> children;
      map<string, llvm::Value*> variables;
  };
}

#endif