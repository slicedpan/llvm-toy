#ifndef VALUE_HPP
#define VALUE_HPP

#include "namespace.hpp"
#include <cstdint>

enum ValueType {
  Integer,
  FloatingPoint,
  String,
  Boolean,
  Function,
  Undefined,
  Nil,
  NativeFunction,
  BuiltinFunction
};

namespace LLVMToy {
  class Function;

  struct Value {
    ValueType type;
    union {
      bool bool_value;
      int64_t int_value;
      double fp_value;
      char* string_value;
      Function* function;
      void* native_function_ptr;
      char short_str[8];
    };
    string to_string() const;
    bool is_truthy();

    static Value make_string(string src);
    static Value make_int(int src);
    static Value make_float(double src);
    static Value make_bool(bool src);
    static Value make_nil();
    static Value make_undefined();
    static Value make_builtin_fn(const char* name);
    
    void free_self();
  };
}

#endif