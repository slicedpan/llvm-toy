#include "llvm_interpreter.hpp"
#include "llvm/Support/TargetSelect.h"
#include "llvm_ir_generator.hpp"
#include "llvm_jit_compiler.hpp"
#include "kaleidoscope_jit.hpp"

namespace LLVMToy {

  static llvm::ExitOnError ExitOnErr;

  LLVMInterpreter::LLVMInterpreter()  {
    
  }

  LLVMInterpreter::~LLVMInterpreter() {
    delete ir_generator;
  }

  void LLVMInterpreter::initialize() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    // auto compiler_result = LLVMJITCompiler::Create();
    // if (!compiler_result) {
    //   llvm::logAllUnhandledErrors(std::move(compiler_result.takeError()), llvm::errs());
    // }
    // compiler = *compiler_result;
    ir_generator = new LLVMIRGenerator();
  }

  void LLVMInterpreter::interpret_statements(const vector<Statement*>& statements) {
    ir_generator->visitStatements(statements);
    ir_generator->print();
  }

  void LLVMInterpreter::run() {
    auto k_jit = ExitOnErr(llvm::orc::KaleidoscopeJIT::Create());
    auto RT = k_jit->getMainJITDylib().createResourceTracker();
    std::unique_ptr<llvm::Module> module_ptr(ir_generator->get_module());
    std::unique_ptr<llvm::LLVMContext> ctx_ptr(&module_ptr->getContext());
    auto tsm = llvm::orc::ThreadSafeModule(std::move(module_ptr), std::move(ctx_ptr));
    k_jit->addModule(std::move(tsm), RT);

    // auto test_symbol = k_jit->lookup("lt_struct_test_fn");
    // assert(test_symbol && "test symbol not found");
    // cout << "test_fn found\n" << endl;
    // double (*test_fn)() = (double (*)())(intptr_t)test_symbol->getAddress();
    // cout << "test_fn returned " << test_fn() << endl;

    auto entrypoint_symbol = k_jit->lookup("entrypoint_fn");
    assert(entrypoint_symbol && "Entrypoint symbol not found");
    cout << "entrypoint_fn found\n" << endl;
    void (*entrypoint_fn)() = (void (*)())(intptr_t)entrypoint_symbol->getAddress();
    entrypoint_fn();
  }

  // void LLVMInterpreter::run() {
  //   auto RT = compiler->getMainJITDylib().createResourceTracker();
  //   std::unique_ptr<llvm::Module> module_ptr(ir_generator->get_module());
  //   std::unique_ptr<llvm::LLVMContext> ctx_ptr(&module_ptr->getContext());
  //   assert(module_ptr.get() && "IRGenerator returned a null Module");
  //   ir_generator->reset_module();
  //   llvm::orc::ThreadSafeModule tsm(std::move(module_ptr), std::move(ctx_ptr));
  //   compiler->addModule(std::move(tsm), RT);

  //   auto test_symbol = compiler->lookup("test_fn");
  //   assert(test_symbol && "test symbol not found");
  //   cout << "test_fn found\n" << endl;
  //   double (*test_fn)() = (double (*)())(intptr_t)test_symbol->getAddress();
  //   cout << "test_fn returned " << test_fn() << endl;

    
  // }
}