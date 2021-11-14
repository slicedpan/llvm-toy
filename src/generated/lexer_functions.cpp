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
    tok.type = LLVMToy::Types::Token::KeywordVar;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_return_empty(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordReturnEmpty;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_return(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordReturn;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_function(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordFunction;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_break(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordBreak;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_for(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordFor;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_if(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordIf;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_keyword_else(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::KeywordElse;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_boolean(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::Boolean;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_floating_point(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::FloatingPoint;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_integer(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::Integer;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_double_equals(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorDoubleEquals;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_equals(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorEquals;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_plus(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorPlus;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_minus(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorMinus;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_not(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorNot;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_multiply(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorMultiply;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_operator_divide(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::OperatorDivide;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_comma(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::Comma;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_string(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::String;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_left_brace(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::LeftBrace;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_right_brace(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::RightBrace;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_left_paren(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::LeftParen;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_right_paren(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::RightParen;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
  void add_identifier(void* userdata, char* content, int line_number) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::Types::Token::Identifier;
    tok.line_number = line_number;
    tok.content.assign(content);
    tokens->push_back(tok);
  }
  
}