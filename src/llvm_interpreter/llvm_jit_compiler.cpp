#include "llvm_jit_compiler.hpp"

namespace LLVMToy {
  llvm::Expected<LLVMJITCompiler*> LLVMJITCompiler::Create() {
    auto EPC = llvm::orc::SelfExecutorProcessControl::Create();
    if (!EPC)
      return EPC.takeError();

    llvm::orc::JITTargetMachineBuilder JTMB((*EPC)->getTargetTriple());
    auto ES = std::make_unique<llvm::orc::ExecutionSession>(std::move(*EPC));

    auto EPCIU = llvm::orc::EPCIndirectionUtils::Create(ES->getExecutorProcessControl());
    if (!EPCIU)
      return EPCIU.takeError();

    (*EPCIU)->createLazyCallThroughManager(
        *ES, llvm::pointerToJITTargetAddress(&handleLazyCallThroughError));

    if (auto Err = setUpInProcessLCTMReentryViaEPCIU(**EPCIU))
      return std::move(Err);

    auto DL = JTMB.getDefaultDataLayoutForTarget();
    if (!DL)
      return DL.takeError();

    LLVMJITCompiler* ret = new LLVMJITCompiler(
      std::move(ES), std::move(*EPCIU),
      std::move(JTMB), std::move(*DL)
    );
    return ret;
  }
}