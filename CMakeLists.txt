cmake_minimum_required (VERSION 2.6)
project(LLVM-Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(llvm-test src/main.cpp src/parser.cpp src/lexer.cpp )