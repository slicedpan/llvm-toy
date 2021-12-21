#include <iostream>
#include <fstream>

#include "boost/format.hpp"
#include "boost/tokenizer.hpp"

#include "namespace.hpp"
#include "lexer.hpp"
#include "token.hpp"

using boost::format;

namespace LexerFunctions {
  void input(char*, void*);
}

namespace LLVMToy {

  void Lexer::print_tokens() {    
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter) { 
      cout << *iter << std::endl;         
    }
  }

  const vector<Token>& Lexer::get_tokens() {
    return tokens;
  }

  void Lexer::lex_file(const string& filename) {
    std::ifstream file_stream(filename);
    file_stream.seekg(0, file_stream.end);
    file_length = file_stream.tellg();
    file_stream.seekg(0, file_stream.beg);

    buffer = new char[file_length];
    file_stream.read(buffer, file_length);
    file_stream.close();
    //LexerFunctions::input(buffer, &(this->tokens));

    current_position = 0;
    current_line = 1;
    last_line_start = 0;

    unsigned int count = 0;

    while(current_position < file_length) {
      consume_whitespace();
      lex_keyword_var();
    }
    emit_token(Types::Token::EndOfFile, "");
    delete[] buffer;
  }

  void Lexer::consume_whitespace(bool include_linebreaks) {
    while (current_position <= file_length) {
      switch (buffer[current_position]) {
        case ' ':
        case '\t':
          current_position += 1;
          break;
        case '\n':
          if (include_linebreaks) {
            current_position += 1;
            current_line += 1;
            last_line_start = current_position;            
          } else {
            return;
          }
          break;
        default:
          return;
      }
    }
  }

  void Lexer::consume_whitespace() {
    consume_whitespace(true);
  }

  string Lexer::peek_until(Types::CharacterClass char_class) {
    stringstream ss;
    unsigned int i = 0;
    while (current_position + i < file_length) {
      char current_char = buffer[current_position + i];
      if (Types::char_in_class(current_char, char_class)) {
        break;
      }
      ss << current_char;
      ++i;
    }
    return ss.str();
  }

  string Lexer::peek_all(Types::CharacterClass char_class) {
    stringstream ss;
    unsigned int i = 0;
    while (current_position + i < file_length) {
      char current_char = buffer[current_position + i];
      if (!Types::char_in_class(current_char, char_class)) {
        break;
      }
      ss << current_char;
      ++i;
    }
    return ss.str();
  }

  bool Lexer::match(string value, Types::CharacterClass char_class){
    if (current_position + value.length() > file_length) {
      return false;
    }
    for (int i = 0; i < value.length(); ++i) {
      if (value[i] != buffer[current_position + i]) {
        return false;
      }
    }
    if (current_position + value.length() == file_length) {
      return true;
    }
    char next_char = buffer[current_position + value.length()];
    return !Types::char_in_class(next_char, char_class);
  }

  bool Lexer::match(string value) {
    return match(value, Types::CharacterClass::ValidIdentifier);
  }

  void Lexer::emit_token(Types::Token token_type, string content) {
    Token tok;
    tok.type = token_type;
    tok.line_number = current_line;
    tok.line_offset = current_position - last_line_start;
    tok.content = content;
    tokens.emplace_back(tok);
  }

  bool Lexer::lex_simple_keyword(Types::Token token_type, string keyword) {
    if (match(keyword)) {
      current_position += keyword.length();
      emit_token(token_type, keyword);
      return true;
    }
    return false;    
  }

  bool Lexer::lex_symbolic_token(Types::Token token_type, string symbol) {
    if (match(symbol, Types::CharacterClass::None)) {
      current_position += symbol.length();
      emit_token(token_type, symbol);
      return true;
    }
    return false;
  }

  void Lexer::lex_keyword_var() {
    if (!lex_simple_keyword(Types::Token::KeywordVar, "var")) {
      lex_keyword_return();
    }
  }

  void Lexer::lex_keyword_return() {
    if (match("return")) {
      current_position += 6;
      consume_whitespace(false);
      if (match("\n")) {
        emit_token(Types::Token::KeywordReturnEmpty, "return");
        consume_whitespace();
      } else {
        emit_token(Types::Token::KeywordReturn, "return");
      }
    } else {
      lex_keyword_function();
    }
  }

  void Lexer::lex_keyword_function() {
    if (!lex_simple_keyword(Types::Token::KeywordFunction, "function")) {
      lex_keyword_break();
    }
  }

  void Lexer::lex_keyword_break() {
    if (!lex_simple_keyword(Types::Token::KeywordBreak, "break")) {
      lex_keyword_for();
    }
  }

  void Lexer::lex_keyword_for() {
    if (!lex_simple_keyword(Types::Token::KeywordFor, "for")) {
      lex_keyword_if();
    }
  }

  void Lexer::lex_keyword_if() {
    if (!lex_simple_keyword(Types::Token::KeywordIf, "if")) {
      lex_keyword_else();
    }
  }

  void Lexer::lex_keyword_else() {
    if (!lex_simple_keyword(Types::Token::KeywordElse, "else")) {
      lex_boolean_literal();
    }
  }

  void Lexer::lex_boolean_literal() {
    if (match("true")) {
      emit_token(Types::Token::Boolean, "true");
      current_position += 4;
    } else if (match("false")) {
      emit_token(Types::Token::Boolean, "false");
      current_position += 5;
    } else {
      lex_numeric_literal();
    }
  }

  void Lexer::lex_numeric_literal() {
    if (Types::char_in_class(buffer[current_position], Types::CharacterClass::Numeric)) {
      stringstream ss;
      unsigned int i = 0;
      bool floating_point = false;
      while (current_position + i < file_length) {
        char current_char = buffer[current_position + i];
        if (Types::char_in_class(current_char, Types::CharacterClass::Numeric)) {
          ss << current_char;
        } else if (current_char == '.') {
          ss << current_char;
          floating_point = true;
        } else {
          break;
        }
        ++i;
      }
      string content = ss.str();
      current_position += content.length();
      if (floating_point) {
        emit_token(Types::Token::FloatingPoint, content);
      } else {
        emit_token(Types::Token::Integer, content);
      }
    } else {
      lex_double_equals();
    }
  }

  void Lexer::lex_double_equals() {
    if (!lex_symbolic_token(Types::Token::OperatorDoubleEquals, "==")) {
      lex_equals();
    }
  }

  void Lexer::lex_equals() {
    if (!lex_symbolic_token(Types::Token::OperatorEquals, "=")) {
      lex_plus();
    }
  }

  void Lexer::lex_plus() {
    if (!lex_symbolic_token(Types::Token::OperatorPlus, "+")) {
      lex_minus();
    }
  }

  void Lexer::lex_minus() {
    if (!lex_symbolic_token(Types::Token::OperatorMinus, "-")) {
      lex_not();
    }
  }

  void Lexer::lex_not() {
    if (!lex_symbolic_token(Types::Token::OperatorNot, "!")) {
      lex_multiply();
    }
  }

  void Lexer::lex_multiply() {
    if (!lex_symbolic_token(Types::Token::OperatorMultiply, "*")) {
      lex_divide();
    }
  }

  void Lexer::lex_divide() {
    if (!lex_symbolic_token(Types::Token::OperatorDivide, "/")) {
      lex_comma();
    }
  }

  void Lexer::lex_comma() {
    if (!lex_symbolic_token(Types::Token::Comma, ",")) {
      lex_string_literal();
    }
  }

  void Lexer::lex_string_literal() {
    if (buffer[current_position] == '"') {      
      stringstream ss;
      unsigned int i = 0;
      current_position += 1; //consume the first double quote
      while (current_position + i < file_length) {
        char current_char = buffer[current_position + i];
        if (current_char == '\\') {
          char next_char = buffer[current_position + i + 1];
          if (next_char == '\\') {
            ss << '\\';
            ++i;
          } else if (next_char == '"') {
            ss << '"';
            ++i;
          } else {
            ss << '\\';
          }
        } else {
          if (current_char == '"') {
            break;
          }
          if (current_char == '\n') {
            current_line += 1;
            last_line_start = current_position + 1;
          }
          ss << current_char;          
        }
        ++i;
      }
      string content = ss.str();
      current_position += i + 1;
      emit_token(Types::Token::String, content);
    } else {
      lex_left_brace();
    }
  }

  void Lexer::lex_left_brace() {
    if (!lex_symbolic_token(Types::Token::LeftBrace, "{")) {
      lex_right_brace();
    }
  }

  void Lexer::lex_right_brace() {
    if (!lex_symbolic_token(Types::Token::RightBrace, "}")) {
      lex_left_paren();
    }
  }

  void Lexer::lex_left_paren() {
    if (!lex_symbolic_token(Types::Token::LeftParen, "(")) {
      lex_right_paren();
    }
  }
  
  void Lexer::lex_right_paren() {
    if (!lex_symbolic_token(Types::Token::RightParen, ")")) {
      lex_identifier();
    }
  }

  void Lexer::lex_identifier() {
    string identifier = peek_all(Types::CharacterClass::ValidIdentifier);
    if (identifier.length() == 0) {
      cout << "Lexer error @ line " << current_line << ", position " << current_position - last_line_start << "\n";
    } else {
      emit_token(Types::Token::Identifier, identifier);
      current_position += identifier.length();
    }
  }
}