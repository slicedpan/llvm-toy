#include "value.hpp"
#include "memory_allocation.hpp"
#include <cstring>

namespace LLVMToy {
  string Value::to_string() const {
    stringstream ss;
    switch (type) {
      case ValueType::Integer:
        ss << int_value << "i";
        break;
      case ValueType::Function:
        ss << "function:" << function;
        break;
      case ValueType::NativeFunction:
        ss << "native_function:" << native_function_ptr;
        break;
      case ValueType::String:
        ss << "\"" << string_value << "\"";
        break;
      case ValueType::FloatingPoint:
        ss << fp_value << "f";
        break;
      case ValueType::Nil:
        ss << "nil";
        break;
      case ValueType::Undefined:
        ss << "undefined";
        break;
      case ValueType::Boolean:
        ss << bool_value ? "true" : "false";
        break;
    }
    return ss.str();
  }

  void Value::free_self() {
    switch (type) {
      case ValueType::String:
        deallocate(string_value);
        break;
      case ValueType::Function:
        delete function;
        break;
    }
  }

  bool Value::is_truthy() {
    switch(type) {
      case ValueType::String:
      case ValueType::Function:
      case ValueType::NativeFunction:
      case ValueType::Integer:
      case ValueType::FloatingPoint:
        return true;
        break;
      case ValueType::Boolean:
        return bool_value;
        break;
    }
    // nil or undefined
    return false;
  }

  Value Value::make_string(string src) {
    Value val;
    size_t memsize = (src.length() + 1) * sizeof(char);
    val.type = ValueType::String;
    val.string_value = (char*)allocate(memsize);
    memcpy(val.string_value, src.c_str(), memsize);
    return val;
  }

  Value Value::make_float(double src) {
    Value val;
    val.type = ValueType::FloatingPoint;
    val.fp_value = src;
    return val;
  }

  Value Value::make_int(int src) {
    Value val;
    val.type = ValueType::Integer;
    val.int_value = src;
    return val;
  }

  Value Value::make_bool(bool src) {
    Value val;
    val.type = ValueType::Boolean;
    val.bool_value = src;
    return val;
  }
}