#ifndef LLVM_INTERPRETER_HPP
#define LLVM_INTERPRETER_HPP

#include "../namespace.hpp"

namespace LLVMToy {
  class Statement;
  class LLVMIRGenerator;
  class LLVMJITCompiler;

  class LLVMInterpreter {
    public:
      LLVMInterpreter();
      ~LLVMInterpreter();
      void initialize();
      void interpret_statements(const vector<Statement*>&);
      void run();
    private:
      LLVMIRGenerator* ir_generator;
      LLVMJITCompiler* compiler;
  };
}

#endif