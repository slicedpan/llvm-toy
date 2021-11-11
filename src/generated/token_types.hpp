#ifndef SRC_TOKEN_TYPES_HPP
#define SRC_TOKEN_TYPES_HPP

#define TOKEN_TYPE_ENTRY(name) {name, #name}

#include "../namespace.hpp"
#include <map>

namespace LLVMToy {

  enum TokenType { KeywordVar,KeywordReturn,KeywordFunction,KeywordBreak,KeyworkFor,Boolean,FloatingPoint,Integer,OperatorEquals,OperatorPlus,OperatorMinus,OperatorNot,OperatorMultiply,OperatorDivide,Comma,String,LeftBrace,RightBrace,LeftParen,RightParen,Identifier,EndOfFile };

  const auto TokenTypeNames = std::map<TokenType, string>{
    {KeywordVar, "KeywordVar"},{KeywordReturn, "KeywordReturn"},{KeywordFunction, "KeywordFunction"},{KeywordBreak, "KeywordBreak"},{KeyworkFor, "KeyworkFor"},{Boolean, "Boolean"},{FloatingPoint, "FloatingPoint"},{Integer, "Integer"},{OperatorEquals, "OperatorEquals"},{OperatorPlus, "OperatorPlus"},{OperatorMinus, "OperatorMinus"},{OperatorNot, "OperatorNot"},{OperatorMultiply, "OperatorMultiply"},{OperatorDivide, "OperatorDivide"},{Comma, "Comma"},{String, "String"},{LeftBrace, "LeftBrace"},{RightBrace, "RightBrace"},{LeftParen, "LeftParen"},{RightParen, "RightParen"},{Identifier, "Identifier"},{EndOfFile, "EndOfFile"}
  };

} //namespace

#endif