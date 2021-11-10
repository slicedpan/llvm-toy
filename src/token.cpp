#include "token.hpp"

namespace LLVMToy {

  ostream& operator<<(ostream& os, const Token& obj)
  {    
    os << obj.line_number << ":" << TokenTypeNames.at(obj.type) << ":" << obj.content;
    return os;
  }

}