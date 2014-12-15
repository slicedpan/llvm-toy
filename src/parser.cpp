#include "parser.hpp"

namespace LLVMToy {

  const std::string binary_operators[] = {
    "+", 
    "-",
    "/",
    "*"
  };

  const std::string keywords[] = {

  };

  const std::string numeric_literal_re = "^\\d+$";

  void Parser::parse(const std::vector<std::string>& tokens) {
    
  }
}