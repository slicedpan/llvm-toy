cmake_minimum_required (VERSION 2.6)
project(LLVM-Test)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_BUILD_TYPE Debug)

find_package(FLEX)

FLEX_TARGET(Lexer src/generated/lexer.l src/yy.lex.cpp)

add_custom_command(
  COMMAND bin/generate_parser
  DEPENDS src/data/tokens.yml src/templates/*
  OUTPUT src/generated/lexer_functions.cpp src/generated/lexer.l src/generated/token_types.hpp
  COMMENT "Generating token types for lexer"
)

add_executable(bin/llvm-test
src/main.cpp 
src/parser.cpp 
src/lexer.cpp 
src/token.cpp
src/generated/lexer_functions.cpp
src/statement.cpp
src/expression.cpp
src/ast/implementations.cpp
src/ast_printer.cpp
src/ast_visitor.cpp
src/value.cpp
src/interpreter/ast_evaluator.cpp
src/interpreter/scope.cpp
src/interpreter/operator_action.cpp
src/memory_allocation.cpp
src/llvm_ir_generator/llvm_ir_generator.cpp
${FLEX_Lexer_OUTPUTS})

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(bin/llvm-test ${llvm_libs})