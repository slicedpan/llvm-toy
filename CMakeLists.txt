cmake_minimum_required (VERSION 2.6)
project(LLVM-Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

find_package(FLEX)

FLEX_TARGET(Lexer src/lexer.l src/yy.lex.cpp)

add_executable(llvm-test 
src/main.cpp 
src/parser.cpp 
src/lexer.cpp 
src/token.cpp 
src/integer_literal_node.cpp
${FLEX_Lexer_OUTPUTS})