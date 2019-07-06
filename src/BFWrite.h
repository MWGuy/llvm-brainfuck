#ifndef LLVM_BF_BFWRITE_H
#define LLVM_BF_BFWRITE_H

#include "BFInstruction.h"

namespace BF {
    class Write : public Instruction {
    public:
        explicit Write(LLVMValueRef cells, LLVMValueRef cellIndex) :
            Instruction(cells, cellIndex) {}

        LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) override;
    };
}
#endif //LLVM_BF_BFWRITE_H
