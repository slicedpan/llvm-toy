#include "character_class.hpp"

namespace LLVMToy {
  namespace Types {
    bool char_in_class(char c, CharacterClass k) {
      switch(k) {
        case Numeric:
          return (c >= '0' && c <= '9');
        case UpperCase:
          return (c >= 'A' && c <= 'Z');
        case LowerCase:
          return (c >= 'a' && c <= 'z');
        case Alpha:
          return (char_in_class(c, LowerCase) || char_in_class(c, UpperCase));
        case AlphaNumeric:
          return (char_in_class(c, Alpha) || char_in_class(c, Numeric));
        case ValidIdentifier:
          return (char_in_class(c, AlphaNumeric) || c == '_' || c == '-');
        case Whitespace:
          return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
        case Any:
          return true;
        case None:
          return false;
      }
    }
  }
}