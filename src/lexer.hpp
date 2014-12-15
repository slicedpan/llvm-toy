#ifndef SRC_LEXER_HPP
#define SRC_LEXER_HPP

#include <string>
#include <vector>

namespace LLVMToy {

class Lexer {
  public:
    void print_tokens();
    void lex_file(const std::string filename);
    const std::vector<std::string>& get_tokens();
  private:
    std::vector<std::string> tokens;
};

} //namespace

#endif