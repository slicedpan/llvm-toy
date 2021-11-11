#include <cstdio>
#include <cstdlib>
#include <exception>
#include "lexer.hpp"
#include "parser.hpp"
#include "parser_error.hpp"

int main(int argc, char** argv) {
  LLVMToy::Lexer lexer;
  lexer.lex_file(argv[1]);
  lexer.print_tokens();
  LLVMToy::Parser parser(lexer.get_tokens());
  try {
    parser.parse();
  } catch (ParserError& e) {
    printf("Error: %s\n", e.what());
  }
  parser.debug_print();
  std::cout << "finished" << std::endl;
}