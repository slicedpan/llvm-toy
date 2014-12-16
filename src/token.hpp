#ifndef SRC_TOKEN_HPP
#define SRC_TOKEN_HPP

#define TOKEN_TYPE_ENTRY(name) {name, #name}

#include "namespace.hpp"
#include <map>

namespace LLVMToy {

  enum TokenType {
    Unknown,
    EndOfFile,
    EndOfLine,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    KeywordDef,
    KeywordExtern,
    Identifier
  };

  const auto TokenTypeNames = std::map<TokenType, string>{
    TOKEN_TYPE_ENTRY(Unknown),
    TOKEN_TYPE_ENTRY(EndOfLine),
    TOKEN_TYPE_ENTRY(EndOfFile),
    TOKEN_TYPE_ENTRY(IntegerLiteral),
    TOKEN_TYPE_ENTRY(FloatLiteral),
    TOKEN_TYPE_ENTRY(StringLiteral),
    TOKEN_TYPE_ENTRY(KeywordDef),
    TOKEN_TYPE_ENTRY(KeywordExtern),
    TOKEN_TYPE_ENTRY(Identifier)
  };

  struct Token {
    TokenType type;    
    string content;    
    int64_t int_val;
    double float_val;
  };

  ostream& operator<<(ostream& os, const Token& obj);

} //namespace

#endif