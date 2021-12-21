#ifndef SRC_LEXER_HPP
#define SRC_LEXER_HPP

#include "namespace.hpp"
#include "token.hpp"
#include "character_class.hpp"

namespace LLVMToy {

class Lexer {
  public:
    void print_tokens();
    void lex_file(const string& filename);
    Token lex_token(const string& v);
    const vector<Token>& get_tokens();
  private:
    bool lex_simple_keyword(Types::Token, string);
    bool lex_symbolic_token(Types::Token, string);
    void lex_eof();
    void lex_keyword_var();
    void lex_keyword_return();
    void lex_keyword_function();
    void lex_keyword_break();
    void lex_keyword_for();
    void lex_keyword_if();
    void lex_keyword_else();
    void lex_boolean_literal();
    void lex_numeric_literal();
    void lex_double_equals();
    void lex_equals();
    void lex_plus();
    void lex_minus();
    void lex_not();
    void lex_divide();
    void lex_multiply();
    void lex_comma();
    void lex_string_literal();
    void lex_left_brace();
    void lex_right_brace();
    void lex_left_paren();
    void lex_right_paren();
    void lex_identifier();
    string peek_until(Types::CharacterClass);
    string peek_all(Types::CharacterClass);
    bool match(string, Types::CharacterClass);
    bool match(string);
    void consume_whitespace();
    void consume_whitespace(bool);
    unsigned int current_position;
    unsigned int current_line;
    unsigned int file_length;
    unsigned int last_line_start;
    vector<Token> tokens;
    char* buffer;
    void emit_token(Types::Token, string);    
};

} //namespace

#endif