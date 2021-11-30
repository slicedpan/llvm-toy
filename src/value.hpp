#ifndef VALUE_HPP
#define VALUE_HPP

#include "namespace.hpp"
#include <cstdint>
#include <cstring>
#include <bitset>
#include "memory_allocation.hpp"

namespace LLVMToy {
  class Function;

  const uint64_t QNAN = 0b0111111111111100000000000000000000000000000000000000000000000000;
  const uint64_t POINTER_BIT = 0b1000000000000000000000000000000000000000000000000000000000000000;
  // including the pointer bit in the type mask means we can directly compare with the initial
  // values like STR_POINTER below
  const uint64_t POINTER_TYPE_MASK = 0b1000000000000000000000000000000000000000000000000000000000000111;
  const uint64_t SHORT_STR_VALUE = 0b0000000000000001000000000000000000000000000000000000000000000000;
  const uint64_t NIL_VALUE = 0b0111111111111100000000000000000000000000000000000000000000000001;
  const uint64_t TRUE_VALUE = 0b0111111111111100000000000000000000000000000000000000000000000010;
  const uint64_t FALSE_VALUE = 0b0111111111111100000000000000000000000000000000000000000000000011;
  const uint64_t UNDEFINED_VALUE = 0b0111111111111100000000000000000000000000000000000000000000000100;
  const uint64_t STR_POINTER = 0b1000000000000000000000000000000000000000000000000000000000000001;
  const uint64_t GENERIC_POINTER = 0b1000000000000000000000000000000000000000000000000000000000000010;
  const uint64_t FUNCTION_POINTER = 0b1000000000000000000000000000000000000000000000000000000000000011;
  const uint64_t POINTER_HI_MASK = 0b0000000000000000111111111111111111111111111111111111111111111000;

  class ValueType {
    public:
      static const uint8_t Integer = 0;
      static const uint8_t FloatingPoint = 1;
      static const uint8_t String = 2;
      static const uint8_t Boolean = 3;
      static const uint8_t Function = 4;
      static const uint8_t Undefined = 5;
      static const uint8_t Nil = 6;
      static const uint8_t NativeFunction = 7;
      static const uint8_t BuiltinFunction = 8;
      static const uint8_t GenericPointer = 9;
      static const uint8_t ShortString = 10;
  };

  struct Value {
    union {
      double float_value;
      void* ptr_value;
      char bytes[8];
      uint64_t uint_value;
    };

    inline string bindump() {
      stringstream ss;
      ss << std::bitset<64>{uint_value};
      return ss.str();
    }

    inline void* pointer_value() {
       return (void*)(uint_value & POINTER_HI_MASK);
    }

    static inline Value make_string(string src) {
      Value val;
      if (src.length() <= 5) {
        val.uint_value = SHORT_STR_VALUE | QNAN;
        char* ptr = &val.bytes[0];
        strcpy(ptr, src.c_str());   
        return val;     
      }
      val.uint_value = STR_POINTER | QNAN;
      char* char_ptr = (char*)allocate(sizeof(char) * (src.length() + 1));
      strcpy(char_ptr, src.c_str());
      char_ptr[src.length()] = '\0';
      val.uint_value |= (uintptr_t)char_ptr & POINTER_HI_MASK;
      return val; 
    }

    inline uint8_t get_type() {
      if ((uint_value & QNAN) != QNAN) {
        return ValueType::FloatingPoint;
      }
      switch (uint_value) {
        case NIL_VALUE:
          return ValueType::Nil;
          break;
        case TRUE_VALUE:
        case FALSE_VALUE:
          return ValueType::Boolean;
          break;
        case UNDEFINED_VALUE:
          return ValueType::Undefined;
          break;
      }
      if ((uint_value & POINTER_BIT)) {
        switch (uint_value & POINTER_TYPE_MASK) {
          case STR_POINTER:
            return ValueType::String;
            break;
          case GENERIC_POINTER:
            return ValueType::GenericPointer;
            break;
          case FUNCTION_POINTER:
            return ValueType::Function;
            break;
        }
      } else {
        return ValueType::ShortString;        
      }
    }

    static inline Value make_number(double src) {
      Value val;
      val.float_value = src;
      return val;
    }

    static inline Value make_nil() {
      Value val;
      val.uint_value = NIL_VALUE;
      return val;
    }

    static inline Value make_undefined() {
      Value val;
      val.uint_value = UNDEFINED_VALUE;
      return val;
    }

    static inline Value make_true() {
      Value val;
      val.uint_value = TRUE_VALUE;
      return val;
    }

    static inline Value make_false() {
      Value val;
      val.uint_value = FALSE_VALUE;
      return val;
    }

    static inline Value make_bool(bool src) {
      return src ? make_true() : make_false();
    }

    static inline Value make_untyped_ptr(void* ptr) {
      Value val;
      val.uint_value = QNAN | ((uintptr_t)ptr & POINTER_HI_MASK);
      return val;
    }

    static inline Value make_generic_ptr(void* ptr) {
      Value val = make_untyped_ptr(ptr);
      val.uint_value |= GENERIC_POINTER;
      return val;
    }

    static inline Value make_function_ptr(void* ptr) {
      Value val = make_untyped_ptr(ptr);
      val.uint_value |= FUNCTION_POINTER;
      return val;
    }

    inline bool is_truthy() {
      return (uint_value != FALSE_VALUE) && 
      (uint_value != NIL_VALUE) && 
      (uint_value != UNDEFINED_VALUE); 
    }

    inline string to_string() {
      stringstream ss;
      switch(get_type()) {
        case ValueType::String:
          ss << (char*)pointer_value();
          break;
        case ValueType::ShortString:
          ss << &bytes[0];
          break;
        case ValueType::FloatingPoint:
          ss << float_value;
          break;
        case ValueType::Nil:
          ss << "nil";
          break;
        case ValueType::Undefined:
          ss << "undefined";
          break;
        case ValueType::Boolean:
          ss << (uint_value == TRUE_VALUE ? "true" : "false");
          break;
        case ValueType::GenericPointer:
          ss << "generic_ptr: " << pointer_value();
          break;
        case ValueType::Function:
          ss << "function: " << pointer_value();
          break;
      }
      return ss.str();
    }

    // static Value make_int(int src);
    // static Value make_float(double src);
    // static Value make_bool(bool src);
    // static Value make_nil();
    // static Value make_undefined();
    // static Value make_builtin_fn(const char* name);
    // static Value make_native_ptr(void* ptr);
    
    // void free_self();


  };
}

#endif