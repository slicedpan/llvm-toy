#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "../namespace.hpp"
#include "../value.hpp"

namespace LLVMToy {
  class Scope {
    public:
      Scope();
      Scope(Scope*);
      ~Scope();
      Value lookup_variable(const string& name);
      void set_variable(const string& name, const Value& value);
      Scope* create_child_scope();
      void debug_print();
    private:
      map<string, Value> variables;
      Scope* parent_scope;
  };
}

#endif