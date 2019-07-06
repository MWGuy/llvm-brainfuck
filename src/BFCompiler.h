#ifndef LLVM_BF_BFCOMPILER_H
#define LLVM_BF_BFCOMPILER_H

#include <string>
#include <vector>
#include <assert.h>
#include <llvm-c/Core.h>
#include "BFInstruction.h"

namespace BF {
    struct BFMain {
        LLVMBasicBlockRef bb;
        LLVMValueRef cells;
        LLVMValueRef cellIndex;
        LLVMValueRef main_function;
    };

    void declareFunctions(LLVMModuleRef module);
    BFMain buildMain(LLVMContextRef context, LLVMModuleRef module, LLVMBuilderRef builder);
    void buildClear(LLVMContextRef context, LLVMModuleRef module, LLVMBuilderRef builder, BFMain data);

    int findClose(std::string source, int index);
    std::vector<BF::Instruction *> parse(const std::string& source, int from, int to, BFMain data);
}

#endif //LLVM_BF_BFCOMPILER_H
