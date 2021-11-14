#ifndef SRC_TOKEN_TYPES_HPP
#define SRC_TOKEN_TYPES_HPP

#define TOKEN_TYPE_ENTRY(name) {name, #name}

#include "../namespace.hpp"
#include <map>

namespace LLVMToy {
  namespace Types {
    enum Token { KeywordVar,KeywordReturnEmpty,KeywordReturn,KeywordFunction,KeywordBreak,KeywordFor,KeywordIf,KeywordElse,Boolean,FloatingPoint,Integer,OperatorDoubleEquals,OperatorEquals,OperatorPlus,OperatorMinus,OperatorNot,OperatorMultiply,OperatorDivide,Comma,String,LeftBrace,RightBrace,LeftParen,RightParen,Identifier,EndOfFile };
    const auto TokenNames = std::map<Token, string>{
      {KeywordVar, "KeywordVar"},{KeywordReturnEmpty, "KeywordReturnEmpty"},{KeywordReturn, "KeywordReturn"},{KeywordFunction, "KeywordFunction"},{KeywordBreak, "KeywordBreak"},{KeywordFor, "KeywordFor"},{KeywordIf, "KeywordIf"},{KeywordElse, "KeywordElse"},{Boolean, "Boolean"},{FloatingPoint, "FloatingPoint"},{Integer, "Integer"},{OperatorDoubleEquals, "OperatorDoubleEquals"},{OperatorEquals, "OperatorEquals"},{OperatorPlus, "OperatorPlus"},{OperatorMinus, "OperatorMinus"},{OperatorNot, "OperatorNot"},{OperatorMultiply, "OperatorMultiply"},{OperatorDivide, "OperatorDivide"},{Comma, "Comma"},{String, "String"},{LeftBrace, "LeftBrace"},{RightBrace, "RightBrace"},{LeftParen, "LeftParen"},{RightParen, "RightParen"},{Identifier, "Identifier"},{EndOfFile, "EndOfFile"}
    };
  }
}

#endif