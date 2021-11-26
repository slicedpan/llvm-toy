#ifndef VALUE_HPP
#define VALUE_HPP

#include "namespace.hpp"
#include <cstdint>


namespace LLVMToy {
  class Function;

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
      static const uint8_t NativePointer = 9;
  };

  struct Value {
    uint8_t type;
    uint8_t pad[7];
    union {
      bool bool_value;
      int64_t int_value;
      double fp_value;
      char* string_value;
      Function* function;
      void* native_ptr;
      char short_str[8];
    };
    string to_string() const;
    string hexdump() const;
    string bindump() const;
    bool is_truthy();

    static Value make_string(string src);
    static Value make_int(int src);
    static Value make_float(double src);
    static Value make_bool(bool src);
    static Value make_nil();
    static Value make_undefined();
    static Value make_builtin_fn(const char* name);
    static Value make_native_ptr(void* ptr);
    
    void free_self();


  };
}

#endif