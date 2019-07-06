#ifndef LLVM_BF_BFCOMPILER_H
#define LLVM_BF_BFCOMPILER_H

#include <llvm-c/Core.h>

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
}

#endif //LLVM_BF_BFCOMPILER_H
