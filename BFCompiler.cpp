#include "BFCompiler.h"

void BF::declareFunctions(LLVMModuleRef module) {
    // types
    LLVMTypeRef void_type  = LLVMVoidType();
    LLVMTypeRef int8_type  = LLVMInt32Type();
    LLVMTypeRef int32_type = LLVMInt32Type();

    // types pointers
    LLVMTypeRef int8_type_ptr = LLVMPointerType(int8_type, 0);

    // calloc
    LLVMTypeRef calloc_function_args_type[] = {
        int32_type, int32_type
    };
    LLVMTypeRef  calloc_function_type = LLVMFunctionType(int8_type_ptr, calloc_function_args_type, 2, false);
    LLVMValueRef calloc_function = LLVMAddFunction(module, "calloc", calloc_function_type);

    // free
    LLVMTypeRef free_function_args_type[] = {
            int8_type_ptr
    };
    LLVMTypeRef  free_function_type = LLVMFunctionType(void_type, free_function_args_type, 1, false);
    LLVMValueRef free_function = LLVMAddFunction(module, "free", free_function_type);

    // putchar
    LLVMTypeRef putchar_function_args_type[] = {
            int32_type
    };
    LLVMTypeRef  putchar_function_type = LLVMFunctionType(int32_type, putchar_function_args_type, 1, false);
    LLVMValueRef putchar_function = LLVMAddFunction(module, "putchar", putchar_function_type);

    // getchar
    LLVMTypeRef  getchar_function_type = LLVMFunctionType(int32_type, nullptr, 0, false);
    LLVMValueRef getchar_function = LLVMAddFunction(module, "getchar", getchar_function_type);
}

BF::BFMain BF::buildMain(LLVMContextRef context, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMTypeRef int32_type = LLVMInt32Type();

    LLVMTypeRef  main_function_type = LLVMFunctionType(int32_type, nullptr, 0, false);
    LLVMValueRef main_function = LLVMAddFunction(module, "main", main_function_type);
    LLVMBasicBlockRef bb = LLVMAppendBasicBlockInContext(context, main_function, "entry");
    LLVMPositionBuilderAtEnd(builder, bb);

    LLVMValueRef calloc_function = LLVMGetNamedFunction(module, "calloc");
    LLVMValueRef calloc_function_args[] {
        LLVMConstInt(int32_type, 30000, false),
        LLVMConstInt(int32_type, 1, false),
    };

    LLVMValueRef cells = LLVMBuildCall(builder, calloc_function, calloc_function_args, 2, "cells");
    LLVMValueRef cellIndex = LLVMBuildAlloca(builder, int32_type, "cell_index_ptr");

    return {
        bb, cells, cellIndex
    };
}

void BF::buildClear(LLVMContextRef context, LLVMModuleRef module, LLVMBuilderRef builder, BFMain data) {
    LLVMValueRef free_function = LLVMGetNamedFunction(module, "free");
    LLVMValueRef free_function_args[] {
        data.cells
    };

    LLVMBuildCall(builder, free_function, free_function_args, 1, "");
    LLVMBuildRet(builder, LLVMConstInt(LLVMInt32TypeInContext(context), 0, false));
}