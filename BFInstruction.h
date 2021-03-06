#ifndef LLVM_BF_BFINSTRUCTION_H
#define LLVM_BF_BFINSTRUCTION_H

#include <llvm-c/Core.h>

namespace BF {
    class Instruction {
    public:
        explicit Instruction(LLVMValueRef cells, LLVMValueRef cellIndex) :
            cells_(cells), cellIndex_(cellIndex) {}

        virtual LLVMBasicBlockRef compile(
                LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) = 0;
    protected:
        LLVMValueRef cells_;
        LLVMValueRef cellIndex_;
    };
}

#endif //LLVM_BF_BFINSTRUCTION_H
