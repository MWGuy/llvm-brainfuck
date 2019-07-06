#include "BFDataIncrement.h"

LLVMBasicBlockRef
BF::DataIncrement::compile(LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) {
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMValueRef cell_index = LLVMBuildLoad(builder, this->cellIndex_, "cell_index");
    LLVMValueRef increment_amount = LLVMConstInt(LLVMInt32Type(), amount_, false);
    LLVMValueRef new_cell_index = LLVMBuildAdd(builder, cell_index, increment_amount, "");

    LLVMBuildStore(builder, new_cell_index, this->cellIndex_);

    return bb;
}
