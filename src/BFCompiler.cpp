#include <iostream>
#include "BFCompiler.h"
#include "BFIncrement.h"
#include "BFDataIncrement.h"
#include "BFReed.h"
#include "BFWrite.h"
#include "BFLoop.h"

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
    LLVMAddFunction(module, "calloc", calloc_function_type);

    // free
    LLVMTypeRef free_function_args_type[] = {
            int8_type_ptr
    };
    LLVMTypeRef  free_function_type = LLVMFunctionType(void_type, free_function_args_type, 1, false);
    LLVMAddFunction(module, "free", free_function_type);

    // putchar
    LLVMTypeRef putchar_function_args_type[] = {
            int32_type
    };
    LLVMTypeRef  putchar_function_type = LLVMFunctionType(int32_type, putchar_function_args_type, 1, false);
    LLVMAddFunction(module, "putchar", putchar_function_type);

    // getchar
    LLVMTypeRef  getchar_function_type = LLVMFunctionType(int32_type, nullptr, 0, false);
    LLVMAddFunction(module, "getchar", getchar_function_type);
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
        bb, cells, cellIndex, main_function
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

int BF::findClose(std::string source, int index) {
    assert((source[index] == '[') &&
           "Looking for ']' but not starting from a '['");

    int count = 0;

    for (int i = index; i < source.length(); ++i) {
        switch (source[i]) {
            case '[':
                count++;
                break;
            case ']':
                count--;
                break;
        }

        if (count == 0) {
            return i;
        }
    }

    return -1;
}

std::vector<BF::Instruction *> BF::parse(const std::string& source, int from, int to, BF::BFMain data) {
    std::vector<BF::Instruction *> prog;

    int i = from;
    while (i < to) {
        switch (source[i]) {
            case '+': {
                prog.push_back(new BF::Increment(data.cells, data.cellIndex));
                break;
            }

            case '-': {
                prog.push_back(new BF::Increment(data.cells, data.cellIndex, -1));
                break;
            }

            case '>': {
                prog.push_back(new BF::DataIncrement(data.cells, data.cellIndex));
                break;
            }

            case '<': {
                prog.push_back(new BF::DataIncrement(data.cells, data.cellIndex, -1));
                break;
            }

            case ',': {
                prog.push_back(new BF::Read(data.cells, data.cellIndex));
                break;
            }

            case '.': {
                prog.push_back(new BF::Write(data.cells, data.cellIndex));
                break;
            }

            case '[': {
                int close = BF::findClose(source, i);

                if (close == -1) {
                    std::cerr << "Unmatched '[' at position " << i << "\n";
                    exit(-3);
                }

                prog.push_back(new BF::Loop(data.cells, data.cellIndex,
                        parse(source, i + 1, close, data)));
                i = close;
                break;
            }

            case ']': {
                std::cerr << "Unmatched ']' at position " << i << "\n";
                exit(-3);
            }
        }

        ++i;
    }

    return prog;
}