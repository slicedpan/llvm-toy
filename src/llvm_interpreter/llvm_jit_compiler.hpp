#ifndef LLVM_JIT_COMPILER_HPP
#define LLVM_JIT_COMPILER_HPP

#include "llvm/IR/DataLayout.h"
#include "llvm/ExecutionEngine/Orc/Mangling.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/IRTransformLayer.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/EPCIndirectionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/ADT/APFloat.h"
#include "../namespace.hpp"

namespace llvm {
  class EPCIndirectionUtils;
}

namespace LLVMToy {
  class LLVMJITCompiler {
    private:
      std::unique_ptr<llvm::orc::ExecutionSession> ES;
      std::unique_ptr<llvm::orc::EPCIndirectionUtils> EPCIU;

      llvm::DataLayout DL;
      llvm::orc::MangleAndInterner Mangle;

      llvm::orc::RTDyldObjectLinkingLayer ObjectLayer;
      llvm::orc::IRCompileLayer CompileLayer;
      llvm::orc::IRTransformLayer OptimizeLayer;

      llvm::orc::JITDylib &MainJD;

      static void handleLazyCallThroughError() {
        llvm::errs() << "LazyCallThrough error: Could not find function body";
        exit(1);
      }

    public:
      LLVMJITCompiler(std::unique_ptr<llvm::orc::ExecutionSession> ES,
                      std::unique_ptr<llvm::orc::EPCIndirectionUtils> EPCIU,
                      llvm::orc::JITTargetMachineBuilder JTMB, llvm::DataLayout DL)
          : ES(std::move(ES)), EPCIU(std::move(EPCIU)), DL(std::move(DL)),
            Mangle(*this->ES, this->DL),
            ObjectLayer(*this->ES,
                        []() { return std::make_unique<llvm::SectionMemoryManager>(); }),
            CompileLayer(*this->ES, ObjectLayer,
                        std::make_unique<llvm::orc::ConcurrentIRCompiler>(std::move(JTMB))),
            OptimizeLayer(*this->ES, CompileLayer, optimizeModule),
            MainJD(this->ES->createBareJITDylib("<main>")) {
        MainJD.addGenerator(
            cantFail(llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(
                DL.getGlobalPrefix())));
      }

      ~LLVMJITCompiler() {
        if (auto Err = ES->endSession())
          ES->reportError(std::move(Err));
        if (auto Err = EPCIU->cleanup())
          ES->reportError(std::move(Err));
      }

      static llvm::Expected<LLVMJITCompiler*> Create();

      const llvm::DataLayout &getDataLayout() const { return DL; }

      llvm::orc::JITDylib &getMainJITDylib() { return MainJD; }

      llvm::Error addModule(llvm::orc::ThreadSafeModule TSM, llvm::orc::ResourceTrackerSP RT = nullptr) {
        if (!RT)
          RT = MainJD.getDefaultResourceTracker();
        
        return OptimizeLayer.add(RT, std::move(TSM));
      }

      llvm::Expected<llvm::JITEvaluatedSymbol> lookup(llvm::StringRef Name) {
        return ES->lookup({&MainJD}, Mangle(Name.str()));
      }

    private:
      static llvm::Expected<llvm::orc::ThreadSafeModule>
      optimizeModule(llvm::orc::ThreadSafeModule TSM, const llvm::orc::MaterializationResponsibility &R) {
        TSM.withModuleDo([](llvm::Module &M) {
          // Create a function pass manager.
          auto FPM = std::make_unique<llvm::legacy::FunctionPassManager>(&M);

          // Add some optimizations.
          FPM->add(llvm::createInstructionCombiningPass());
          FPM->add(llvm::createReassociatePass());
          FPM->add(llvm::createGVNPass());
          FPM->add(llvm::createCFGSimplificationPass());
          FPM->doInitialization();

          // Run the optimizations over all functions in the module being added to
          // the JIT.
          for (auto &F : M)
            FPM->run(F);
        });

        return std::move(TSM);
      }

  };
}

#endif