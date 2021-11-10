#ifndef SRC_TOKEN_TYPES_HPP
#define SRC_TOKEN_TYPES_HPP

#define TOKEN_TYPE_ENTRY(name) {name, #name}

#include "../namespace.hpp"
#include <map>

namespace LLVMToy {

  enum TokenType { KeywordVar,KeywordReturn,KeywordFunction,KeywordBreak,KeyworkFor,FloatingPointLiteral,Integer,Operator,String,LeftBrace,RightBrace,LeftParen,RightParen,IntegerLiteral,StringLiteral,Identifier };

  const auto TokenTypeNames = std::map<TokenType, string>{
    {KeywordVar, "KeywordVar"},{KeywordReturn, "KeywordReturn"},{KeywordFunction, "KeywordFunction"},{KeywordBreak, "KeywordBreak"},{KeyworkFor, "KeyworkFor"},{FloatingPointLiteral, "FloatingPointLiteral"},{Integer, "Integer"},{Operator, "Operator"},{String, "String"},{LeftBrace, "LeftBrace"},{RightBrace, "RightBrace"},{LeftParen, "LeftParen"},{RightParen, "RightParen"},{IntegerLiteral, "IntegerLiteral"},{StringLiteral, "StringLiteral"},{Identifier, "Identifier"}
  };

} //namespace

#endif