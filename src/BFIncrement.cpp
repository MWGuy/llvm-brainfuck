#include "BFIncrement.h"

LLVMBasicBlockRef BF::Increment::compile(
        LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) {
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMValueRef cell_index = LLVMBuildLoad(builder, this->cellIndex_, "cell_index");
    LLVMValueRef current_cell_ptr = LLVMBuildGEP(builder, this->cells_, &cell_index, 1, "current_cell_ptr");

    LLVMValueRef cell_value = LLVMBuildLoad(builder, current_cell_ptr, "cell_value");
    LLVMValueRef new_call_value = LLVMBuildAdd(
            builder, cell_value, LLVMConstInt(LLVMInt32Type(), amount_, false), "cell_value");

    LLVMBuildStore(builder, new_call_value, current_cell_ptr);
    return bb;
}
