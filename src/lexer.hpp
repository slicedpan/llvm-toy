#ifndef SRC_LEXER_HPP
#define SRC_LEXER_HPP

#include "namespace.hpp"
#include "token.hpp"

namespace LLVMToy {

class Lexer {
  public:
    void print_tokens();
    void lex_file(const string& filename);
    Token lex_token(const string& v);
    const vector<Token>& get_tokens();
  private:
    vector<Token> tokens;
};

} //namespace

#endif