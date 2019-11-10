#include "BFReed.h"

LLVMBasicBlockRef
BF::Read::compile(
        LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) {
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMValueRef getchar_function = LLVMGetNamedFunction(module, "getchar");
    LLVMValueRef input_char = LLVMBuildCall(builder, getchar_function, nullptr, 0, "input_char");
    LLVMValueRef input_byte = LLVMBuildTrunc(builder, input_char, LLVMInt32Type(), "input_byte");

    LLVMBuildStore(builder, input_byte, this->cellIndex_);

    return bb;
}
