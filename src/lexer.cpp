#include <iostream>
#include <fstream>

#include "boost/format.hpp"
#include "boost/tokenizer.hpp"

#include "namespace.hpp"
#include "lexer.hpp"

using boost::format;

namespace LLVMToy {

  void Lexer::print_tokens() {    
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter) { 
      cout << *iter;         
    }
  }

  const vector<Token>& Lexer::get_tokens() {
    return tokens;
  }

  void Lexer::lex_file(const string& filename) {
    std::ifstream file_stream(filename);
    string line;
    boost::char_separator<char> sep(" ");    

    while (std::getline(file_stream, line)) {
      boost::tokenizer<boost::char_separator<char> > tok(line, sep);
      for (auto iter = tok.begin(); iter != tok.end(); ++iter) {
        tokens.push_back(lex_token(*iter));
      }      
    }
  }

  Token Lexer::lex_token(const string& content) {
    Token tok;
    tok.content = content;
    
    std::size_t pos = 0;
    if (content.compare("def")) {
      tok.type = TokenType::KeywordDef;
      return tok;
    }
    else if (content.compare("extern")) {
      tok.type = TokenType::KeywordExtern;
      return tok;
    }

    tok.int_val = std::stoll(content, &pos, 0);
    if (pos == content.length()) {
      tok.type = TokenType::IntegerLiteral;
      return tok;
    }

    tok.float_val = std::stod(content, &pos);
    if (pos == content.length()) {
      tok.type = TokenType::FloatLiteral;
      return tok;
    }

    tok.type = TokenType::StringLiteral;    
    return tok;
  }

}