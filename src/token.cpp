#include "token.hpp"

namespace LLVMToy {

  ostream& operator<<(ostream& os, const Token& obj)
  {
    // for (auto it = TokenTypeNames.begin(); it != TokenTypeNames.end(); ++it) {
    //   std::cout << it->first << ": " << it->second << std::endl;
    // }
    // std::cout << "Value: " << obj.type << std::endl;
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