#include <iostream>
#include <fstream>
#include <vector>
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

    std::string source((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef  module = LLVMModuleCreateWithNameInContext("brainfuck", context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    BF::declareFunctions(module);
    BF::BFMain data = BF::buildMain(context, module, builder);
    auto prog = BF::parse(source, 0, source.length(), data);

    for (auto instruction: prog)
        data.bb = instruction->compile(context, module, data.main_function, data.bb);

    for (auto instruction: prog)
        delete instruction;

    LLVMPositionBuilderAtEnd(builder, data.bb);
    BF::buildClear(context, module, builder, data);

    //LLVMDumpModule(module);
    LLVMPrintModuleToFile(module, "test.ll", nullptr);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    return 0;
}