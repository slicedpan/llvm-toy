#include <cstdio>
#include <cstdlib>
#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char** argv) {
  LLVMToy::Lexer lexer;
  LLVMToy::Parser parser;
  lexer.lex_file(argv[1]);
  lexer.print_tokens();
  parser.parse(lexer.get_tokens());
}