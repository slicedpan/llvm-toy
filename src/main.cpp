#include <cstdio>
#include <cstdlib>
#include <exception>
#include "lexer.hpp"
#include "parser.hpp"
#include "parser_error.hpp"
#include "statement.hpp"
#include "ast_printer.hpp"
#include "interpreter/ast_evaluator.hpp"
#include "interpreter/scope.hpp"
#include <cassert>
#include "llvm_interpreter/llvm_ir_generator.hpp"
#include "llvm_interpreter/llvm_interpreter.hpp"

int main(int argc, char** argv) {
  LLVMToy::Lexer lexer;
  lexer.lex_file(argv[1]);
  lexer.print_tokens();
  LLVMToy::Parser parser(lexer.get_tokens());
  printf("\n");
  try {
    parser.parse();
  } catch (ParserError& e) {
    printf("Error: %s\n", e.what());
  }

  LLVMToy::ASTPrinter debug_printer;
  debug_printer.print(parser.get_statements());

  // LLVMToy::LLVMIRGenerator ir_generator;
  // ir_generator.visitStatements(parser.get_statements());
  // ir_generator.print();

  LLVMToy::LLVMInterpreter interpreter;
  interpreter.initialize();
  interpreter.interpret_statements(parser.get_statements());
  interpreter.run();

  // LLVMToy::ASTEvaluator evaluator;
  // LLVMToy::Scope base_scope;
  // evaluator.evaluate(parser.get_statements(), &base_scope);
  // base_scope.debug_print();
}