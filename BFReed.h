#ifndef LLVM_BF_BFREED_H
#define LLVM_BF_BFREED_H

#include "BFInstruction.h"

namespace BF {
    class Read : public Instruction {
    public:
        explicit Read(LLVMValueRef cells, LLVMValueRef cellIndex) :
            Instruction(cells, cellIndex) {}

        LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) override;
    };
}

#endif //LLVM_BF_BFREED_H
