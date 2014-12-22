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

  typedef std::vector<LLVMToy::Token>* tokens_ptr;

  void add_integer(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::IntegerLiteral;
    tok.content.assign(content);
    tok.int_val = std::stoll(content);
    tokens->push_back(tok);
  }

  void add_float(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::FloatLiteral;
    tok.content.assign(content);
    tok.float_val = std::stod(content);
    tokens->push_back(tok);
  }

  void add_string(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.type = LLVMToy::TokenType::StringLiteral;
    tok.content.assign(content);
    tokens->push_back(tok);
  }

  void add_operator(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.content.assign(content);
    tok.type = LLVMToy::TokenType::Operator;
    tokens->push_back(tok);
  }

  void add_keyword_def(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.content.assign(content);
    tok.type = LLVMToy::TokenType::KeywordDef;
    tokens->push_back(tok);
  }

  void add_keyword_extern(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.content.assign(content);
    tok.type = LLVMToy::TokenType::KeywordExtern;
    tokens->push_back(tok);
  }

  void add_identifier(void* userdata, char* content) {
    auto tokens = (tokens_ptr)userdata;
    LLVMToy::Token tok;
    tok.content.assign(content);
    tok.type = LLVMToy::TokenType::Identifier;
    tokens->push_back(tok);
  }

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
    int length = file_stream.tellg();
    file_stream.seekg(0, file_stream.beg);

    char* buffer = new char[length];
    file_stream.read(buffer, length);
    file_stream.close();
    LexerFunctions::input(buffer, &(this->tokens));
    delete[] buffer;
  }

}