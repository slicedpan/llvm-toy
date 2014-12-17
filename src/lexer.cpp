#include <iostream>
#include <fstream>

#include "boost/format.hpp"
#include "boost/tokenizer.hpp"

#include "namespace.hpp"
#include "lexer.hpp"
#include "token.hpp"

using boost::format;

void lexer_input(char*, void*);

void lexer_add_integer(void* userdata, char* content) {
  auto tokens = (std::vector<LLVMToy::Token>*)userdata;
  LLVMToy::Token tok;
  tok.type = LLVMToy::TokenType::IntegerLiteral;
  tok.content = content;
  tok.int_val = std::stoll(content);
  tokens->push_back(tok);
}

void lexer_add_float(void* userdata, char* content) {
  auto tokens = (std::vector<LLVMToy::Token>*)userdata;
  LLVMToy::Token tok;
  tok.type = LLVMToy::TokenType::FloatLiteral;
  tok.content = content;
  tok.float_val = std::stod(content);
  tokens->push_back(tok);
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
    lexer_input(buffer, &(this->tokens));
    delete[] buffer;
  }

}