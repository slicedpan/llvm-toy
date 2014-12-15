#include <iostream>
#include <fstream>

#include "boost/format.hpp"
#include "boost/tokenizer.hpp"

#include "lexer.hpp"

using boost::format;

namespace LLVMToy {
  void Lexer::print_tokens() {
    bool lbracket = true;
    for (auto iter = tokens.begin(); iter != tokens.end(); ++iter) { 
      if (lbracket) {
        lbracket = false;
        std::cout << "[";
      }
      std::cout << ":" << *iter << ", ";
      if ((*iter).compare("new_line") == 0) {
        std::cout << "]" << std::endl;
        lbracket = true;
      }      
    }
  }

  const std::vector<std::string>& Lexer::get_tokens() {
    return tokens;
  }

  void Lexer::lex_file(const std::string filename) {
    std::ifstream file_stream(filename);
    std::string line;
    boost::char_separator<char> sep(" ");

    while (std::getline(file_stream, line)) {
      boost::tokenizer<boost::char_separator<char> > tok(line, sep);
      for (auto iter = tok.begin(); iter != tok.end(); ++iter) {
        tokens.push_back(*iter);
      }
      tokens.push_back("new_line");
    }
  }

}