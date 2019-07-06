#ifndef LLVM_BF_BFDATAINCREMENT_H
#define LLVM_BF_BFDATAINCREMENT_H

#include "BFInstruction.h"

namespace BF {
    class DataIncrement : public Instruction {
    public:
        explicit DataIncrement(LLVMValueRef cells, LLVMValueRef cellIndex) :
            Instruction(cells, cellIndex), amount_(1) {}

        explicit DataIncrement(LLVMValueRef cells, LLVMValueRef cellIndex, int amount) :
            Instruction(cells, cellIndex), amount_(amount) {}

        LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) override;
    private:
        int amount_;
    };
}

#endif //LLVM_BF_BFDATAINCREMENT_H
