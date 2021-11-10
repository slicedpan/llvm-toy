#include <iostream>
#include <fstream>

#include "boost/format.hpp"
#include "boost/tokenizer.hpp"

#include "../namespace.hpp"
#include "../lexer.hpp"
#include "../token.hpp"

using boost::format;

namespace LexerFunctions {
  typedef std::vector<LLVMToy::Token>* tokens_ptr;

  
  void add_keyword_var(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::KeywordVar;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_return(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::KeywordReturn;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_function(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::KeywordFunction;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_break(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::KeywordBreak;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keywork_for(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::KeyworkFor;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_floating_point_literal(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::FloatingPointLiteral;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_integer(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Integer;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Operator;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_string(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::String;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_left_brace(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::LeftBrace;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_right_brace(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::RightBrace;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_left_paren(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::LeftParen;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_right_paren(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::RightParen;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_integer_literal(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::IntegerLiteral;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_string_literal(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::StringLiteral;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_identifier(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Identifier;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
}