#include "llvm_interpreter.hpp"
#include "llvm/Support/TargetSelect.h"
#include "./llvm_ir_generator.hpp"
#include "./llvm_jit_compiler.hpp"

namespace LLVMToy {
  LLVMInterpreter::LLVMInterpreter()  {
    
  }

  LLVMInterpreter::~LLVMInterpreter() {
    delete ir_generator;
  }

  void LLVMInterpreter::initialize() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    auto compiler_result = LLVMJITCompiler::Create();
    if (!compiler_result) {
      llvm::logAllUnhandledErrors(std::move(compiler_result.takeError()), llvm::errs());
    }
    compiler = *compiler_result;
    ir_generator = new LLVMIRGenerator();
  }

  void LLVMInterpreter::interpret_statements(const vector<Statement*>& statements) {
    ir_generator->visitStatements(statements);
    ir_generator->print();
  }

  void LLVMInterpreter::run() {
    llvm::orc::ThreadSafeContext tsc;
    std::unique_ptr<llvm::Module> module_ptr(ir_generator->get_module());
    ir_generator->reset_module();
    llvm::orc::ThreadSafeModule tsm(std::move(module_ptr), tsc);
    compiler->addModule(std::move(tsm));
  }
}