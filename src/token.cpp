#include "token.hpp"

namespace LLVMToy {

  ostream& operator<<(ostream& os, const Token& obj)
  {    
    os << TokenTypeNames.at(obj.type) << ":";
    if (obj.type == TokenType::FloatLiteral) {
      os << obj.float_val;
    }
    else if (obj.type == TokenType::IntegerLiteral) {
      os << obj.int_val;
    }
    else {
      os << obj.content;
    }
    return os;
  }

}