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
    int length = file_stream.tellg();
    file_stream.seekg(0, file_stream.beg);

    char* buffer = new char[length + 1];
    file_stream.read(buffer, length);
    file_stream.close();
    buffer[length] = '\0';
    LexerFunctions::input(buffer, &(this->tokens));
    Token last_token;
    last_token.line_number = -1;
    last_token.type = Types::Token::EndOfFile;
    last_token.content = "";
    tokens.push_back(last_token);
    delete[] buffer;
  }

}