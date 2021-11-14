#ifndef VALUE_HPP
#define VALUE_HPP

#include "function.hpp"
#include "namespace.hpp"

enum ValueType {
  Integer,
  FloatingPoint,
  String,
  Boolean,
  Function,
  Undefined,
  Nil,
  NativeFunction
};
namespace LLVMToy {

  struct Value {
    ValueType type;
    union {
      bool bool_value;
      int int_value;
      double fp_value;
      char* string_value;
      Function* function;
      void* native_function_ptr;
    };
    string to_string() const;
    bool is_truthy();

    static Value make_string(string src);
    static Value make_int(int src);
    static Value make_float(double src);
    static Value make_bool(bool src);
    
    void free_self();
  };
}

#endif