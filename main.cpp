#include <iostream>
#include <fstream>
#include <vector>
#include "BFCompiler.h"
#include "BFIncrement.h"
#include "BFDataIncrement.h"
#include "BFReed.h"
#include "BFWrite.h"

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

    std::vector<BF::Instruction *> prog;

    for (char i : source) {
        switch (i) {
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
        }
    }

    for (auto instruction: prog)
        data.bb = instruction->compile(context, module, data.main_function, data.bb);

    for (auto instruction: prog)
        delete instruction;

    BF::buildClear(context, module, builder, data);

    //LLVMDumpModule(module);
    LLVMPrintModuleToFile(module, "test.ll", nullptr);

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    return 0;
}