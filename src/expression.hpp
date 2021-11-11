#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

namespace LLVMToy {
  class Expression {
    public:
      virtual void debug_print(int indent);
      virtual bool assignable() { return false; }
    protected:
      void tab(int indent);      
  };
}
#endif