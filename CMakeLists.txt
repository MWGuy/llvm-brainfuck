cmake_minimum_required(VERSION 3.14)
project(llvm_bf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -lLLVM)

add_executable(llvm_bf main.cpp BFCompiler.cpp BFInstruction.h BFCompiler.cpp BFCompiler.h BFIncrement.cpp BFIncrement.h BFReed.cpp BFReed.h BFWrite.cpp BFWrite.h BFDataIncrement.cpp BFDataIncrement.h BFLoop.cpp BFLoop.h)