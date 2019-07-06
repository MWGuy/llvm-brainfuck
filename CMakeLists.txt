cmake_minimum_required(VERSION 3.14)
project(llvm_bf)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -lLLVM)

add_executable(llvm_bf main.cpp src/BFCompiler.cpp src/BFInstruction.h src/BFCompiler.cpp src/BFCompiler.h src/BFIncrement.cpp src/BFIncrement.h src/BFReed.cpp src/BFReed.h src/BFWrite.cpp src/BFWrite.h src/BFDataIncrement.cpp src/BFDataIncrement.h src/BFLoop.cpp src/BFLoop.h)