#include <utility>

#ifndef LLVM_BF_BFLOOP_H
#define LLVM_BF_BFLOOP_H

#include <vector>
#include "BFInstruction.h"

namespace BF {
    class Loop : public Instruction {
    public:
        explicit Loop(LLVMValueRef cells, LLVMValueRef cellIndex, std::vector<BF::Instruction *> loop) :
            Instruction(cells, cellIndex), loop_(std::move(loop)) {}

        LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) override;
    private:
        std::vector<BF::Instruction *> loop_;
    };
}

#endif //LLVM_BF_BFLOOP_H
