#include <iostream>
#include <fstream>
#include "BFCompiler.h"

int main(int argc, char ** argv) {

    if (argc != 2) {
        std::cerr << "Usage: llvm_bf <file.bf>" << std::endl;
        return -1;
    }

    auto ifs = std::ifstream(argv[1]);
    if (!ifs) {
        std::cerr << "Unable open file: " << argv[1] << std::endl;
        return -2;
    }

    std::string source;
    ifs >> source;

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef  module = LLVMModuleCreateWithNameInContext("brainfuck", context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    BF::declareFunctions(module);
    BF::BFMain data = BF::buildMain(context, module, builder);

    // TODO: compile here

    BF::buildClear(context, module, builder, data);

    //LLVMDumpModule(module);
    LLVMPrintModuleToFile(module, "test.ll", nullptr);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    return 0;
}