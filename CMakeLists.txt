cmake_minimum_required (VERSION 2.6)
project(LLVM-Test)

find_package(LLVM REQUIRED CONFIG)
find_package(Catch2 3 REQUIRED)

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
  
llvm_map_components_to_libnames(llvm_libs support core irreader x86asmparser target x86codegen orcjit)

file(GLOB TESTS ./test/*.cpp)

add_executable(tests
src/value.cpp
src/memory_allocation.cpp
${TESTS}
)

target_link_libraries(tests PRIVATE ${llvm_libs} Catch2::Catch2WithMain)

add_executable(llvm-test
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
src/llvm_interpreter/llvm_ir_generator.cpp
src/llvm_interpreter/llvm_interpreter.cpp
src/llvm_interpreter/llvm_jit_compiler.cpp
src/llvm_interpreter/llvm_builtins.cpp
src/llvm_interpreter/debug_printer.cpp
src/character_class.cpp
${FLEX_Lexer_OUTPUTS}
)

target_link_libraries(llvm-test ${llvm_libs})

include(CTest)
include(Catch)
catch_discover_tests(tests)