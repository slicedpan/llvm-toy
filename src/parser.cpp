#include "parser.hpp"
#include "token.hpp"

namespace LLVMToy {

  const std::string binary_operators[] = {
    "+", 
    "-",
    "/",
    "*",
    ":="
  };

  const std::string keywords[] = {
    "if",
    "then",
    "else",
    "elseif"
  };

  const std::string control_characters[] = {
    "{",
    "}"
  };

  const std::string literal_markers[] = {
    "\"",
    "'"
  };

  const std::string numeric_literal_re = "^\\d+$";

  void Parser::parse(const vector<Token>& tokens) {    
    for (int i = 0; i < tokens.size(); ++i) {
      bool last_token = (i >= tokens.size() - 1);
      string token = tokens[i].content;
    }
  }

  AbstractSyntaxTree& Parser::get_abstract_syntax_tree() {
    return ast;
  }

}