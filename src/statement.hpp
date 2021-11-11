#ifndef STATEMENT_HPP
#define STATEMENT_HPP

namespace LLVMToy {
  class Statement {
    public:    
      virtual void debug_print(int indent);
    protected:
      void tab(int count);
  };
}

#endif