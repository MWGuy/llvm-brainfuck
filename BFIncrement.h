#ifndef LLVM_BF_BFINCREMENT_H
#define LLVM_BF_BFINCREMENT_H

#include "BFInstruction.h"

namespace BF {
    class Increment : public Instruction {
    public:
        explicit Increment(LLVMValueRef cells, LLVMValueRef cellIndex) :
            amount_(1), Instruction(cells, cellIndex) {}

        explicit Increment(LLVMValueRef cells, LLVMValueRef cellIndex, int amount) :
            amount_(amount), Instruction(cells, cellIndex) {}

        LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) override;
    private:
        int amount_;
    };
}

#endif //LLVM_BF_BFINCREMENT_H
