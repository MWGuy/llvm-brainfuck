#include "BFWrite.h"

LLVMBasicBlockRef
BF::Write::compile(LLVMContextRef context, LLVMModuleRef module, LLVMValueRef function, LLVMBasicBlockRef bb) {
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMValueRef cell_index = LLVMBuildLoad(builder, this->cellIndex_, "cell_index");
    LLVMValueRef current_cell_ptr = LLVMBuildGEP(builder, this->cells_, &cell_index, 1, "current_cell_ptr");

    LLVMValueRef cell_value = LLVMBuildLoad(builder, current_cell_ptr, "cell_value");
    LLVMValueRef cell_val_as_char = LLVMBuildSExt(builder, cell_value, LLVMInt32Type(), "cell_val_as_char");

    LLVMValueRef putchar_function = LLVMGetNamedFunction(module, "putchar");
    LLVMValueRef putchar_function_args[] {
        cell_val_as_char
    };

    LLVMBuildCall(builder, putchar_function, putchar_function_args, 1, "");

    return bb;
}
