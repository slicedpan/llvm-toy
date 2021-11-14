#ifndef OPERATOR_TYPES_HPP
#define OPERATOR_TYPES_HPP

#include "generated/token_types.hpp"

namespace LLVMToy {
  namespace Types {
    enum Operator {
      Plus,
      Minus,
      Divide,
      Multiply,
      Equals,
      DoubleEquals,
      NotEquals,
      Not
    };
    const auto OperatorNames = map<Operator, string>{
      {Plus, "Plus"},
      {Minus, "Minus"},
      {Divide, "Divide"},
      {Multiply, "Multiply"},
      {Equals, "Equals"},
      {DoubleEquals, "DoubleEquals"},
      {NotEquals, "NotEquals"},
      {Not, "Not"}
    };
    const auto TokenToOperator = map<Token, Operator>{
      {Token::OperatorDivide, Divide},
      {Token::OperatorMinus, Minus},
      {Token::OperatorDivide, Divide},
      {Token::OperatorMultiply, Multiply},
      {Token::OperatorPlus, Plus},
      {Token::OperatorNot, Not}
    };
  }
}

#endif