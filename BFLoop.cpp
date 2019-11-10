#include "BFLoop.h"

LLVMBasicBlockRef
BF::Loop::compile(LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) {
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMBasicBlockRef loop_header = LLVMAppendBasicBlock(function, "loop_header");
    LLVMBuildBr(builder, loop_header);

    LLVMBasicBlockRef loop_body  = LLVMAppendBasicBlock(function, "loop_body");
    LLVMBasicBlockRef loop_after  = LLVMAppendBasicBlock(function, "loop_after");

    LLVMPositionBuilderAtEnd(builder, loop_header);
    LLVMValueRef cell_index = LLVMBuildLoad(builder, this->cellIndex_, "cell_index");
    LLVMValueRef current_cell_ptr = LLVMBuildGEP(builder, this->cells_, &cell_index, 1, "current_cell_ptr");
    LLVMValueRef cell_value = LLVMBuildLoad(builder, current_cell_ptr, "cell_value");

    LLVMValueRef cell_value_is_zero = LLVMBuildICmp(builder, LLVMIntPredicate::LLVMIntEQ, cell_value,
            LLVMConstInt(LLVMInt32Type(), 0, false), "");

    LLVMBuildCondBr(builder, cell_value_is_zero, loop_after, loop_body);

    for (auto it : loop_)
        loop_body = it->compile(context, module, function, loop_body);

    LLVMPositionBuilderAtEnd(builder, loop_body);
    LLVMBuildBr(builder, loop_header);

    return loop_after;
}
