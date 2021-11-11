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
  
  void add_boolean(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Boolean;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_floating_point(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::FloatingPoint;
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
  
  void add_operator_equals(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorEquals;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_plus(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorPlus;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_minus(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorMinus;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_not(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorNot;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_multiply(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorMultiply;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_divide(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::OperatorDivide;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_comma(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Comma;
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
  
  void add_identifier(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::Identifier;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
}