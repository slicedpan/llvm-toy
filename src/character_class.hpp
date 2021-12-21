#ifndef CHARACTER_CLASSES_HPP
#define CHARACTER_CLASSES_HPP

namespace LLVMToy {
  namespace Types {
    enum CharacterClass {
      UpperCase,
      LowerCase,
      Numeric,
      Alpha,
      AlphaNumeric,
      ValidIdentifier,
      Whitespace,
      Any,
      None
    };
    bool char_in_class(char, CharacterClass);
  }  
}

#endif