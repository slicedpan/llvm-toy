#ifndef SRC_TOKEN_HPP
#define SRC_TOKEN_HPP

#define TOKEN_TYPE_ENTRY(name) {name, #name}

#include "namespace.hpp"
#include "generated/token_types.hpp"
#include <map>

namespace LLVMToy {  

  struct Token {
    TokenType type;
    int line_number;    
    string content;
  };

  ostream& operator<<(ostream& os, const Token& obj);

} //namespace

#endif