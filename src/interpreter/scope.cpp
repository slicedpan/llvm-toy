#include "scope.hpp"

namespace LLVMToy {
  Scope::Scope(Scope* parent_scope) : Scope() {
    this->parent_scope = parent_scope;    
  }

  Scope::Scope() {}
  Scope::~Scope() {
    
  }

  Value Scope::lookup_variable(const string& name) {
    if (variables.count(name) == 0) {
      if (parent_scope) {
        return parent_scope->lookup_variable(name);
      }
      return Value::make_undefined();
    }
    return variables[name];
  }

  void Scope::set_variable(const string& name, const Value& value) {
    variables[name] = value;
  }

  Scope* Scope::create_child_scope() {
    return new Scope(this);
  }

  void Scope::debug_print() {
    for (auto iter = variables.begin(); iter != variables.end(); ++iter) {
      cout << (*iter).first << ": " << (*iter).second.to_string() << endl;
    }
  }
}