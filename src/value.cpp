// #include "value.hpp"
// #include "memory_allocation.hpp"
// #include <cstring>
// #include <bitset>

// namespace LLVMToy {
//   string Value::hexdump() const {
//     stringstream ss;
//     ss << std::hex << type << pad[0] << pad[1] << pad[2] << pad[3] << pad[4] << pad[5] << pad[6] << int_value;
//     return ss.str();
//   }

//   string Value::bindump() const {
//     stringstream ss;
//     ss << std::bitset<8>{type} << std::bitset<8>{pad[0]} << std::bitset<8>{pad[1]} << std::bitset<8>{pad[2]}
//       << std::bitset<8>{pad[3]} << std::bitset<8>{pad[4]} << std::bitset<8>{pad[5]} << std::bitset<8>{pad[6]}
//       << std::bitset<64>{int_value};
//     return ss.str();
//   }

//   string Value::to_string() const {
//     stringstream ss;
//     switch (type) {
//       case ValueType::Integer:
//         ss << int_value << "i";
//         break;
//       case ValueType::Function:
//         ss << "function:" << function;
//         break;
//       case ValueType::NativeFunction:
//         ss << "native_function:" << native_ptr;
//         break;
//       case ValueType::String:
//         ss << "\"" << string_value << "\"";
//         break;
//       case ValueType::FloatingPoint:
//         ss << fp_value << "f";
//         break;
//       case ValueType::Nil:
//         ss << "nil";
//         break;
//       case ValueType::Undefined:
//         ss << "undefined";
//         break;
//       case ValueType::Boolean:
//         ss << (bool_value ? "true" : "false");
//         break;
//       case ValueType::NativePointer:
//         ss << "ptr: " << native_ptr;
//         break;
//     }
//     return ss.str();
//   }

//   void Value::free_self() {
//     switch (type) {
//       case ValueType::String:
//         deallocate(string_value);
//         break;
//       case ValueType::Function:
//         delete function;
//         break;
//     }
//   }

//   bool Value::is_truthy() {
//     switch(type) {
//       case ValueType::String:
//       case ValueType::Function:
//       case ValueType::NativeFunction:
//       case ValueType::Integer:
//       case ValueType::FloatingPoint:
//         return true;
//         break;
//       case ValueType::Boolean:
//         return bool_value;
//         break;
//     }
//     // nil or undefined
//     return false;
//   }

//   Value Value::make_native_ptr(void* ptr) {
//     Value val{ ValueType::NativePointer };
//     val.native_ptr = ptr;
//     return val;
//   }

//   Value Value::make_string(string src) {
//     Value val;
//     size_t memsize = (src.length() + 1) * sizeof(char);
//     val.type = ValueType::String;
//     val.string_value = (char*)allocate(memsize);
//     memcpy(val.string_value, src.c_str(), memsize);
//     return val;
//   }

//   Value Value::make_float(double src) {
//     Value val;
//     val.type = ValueType::FloatingPoint;
//     val.fp_value = src;
//     return val;
//   }

//   Value Value::make_int(int src) {
//     Value val;
//     val.type = ValueType::Integer;
//     val.int_value = src;
//     return val;
//   }

//   Value Value::make_bool(bool src) {
//     Value val;
//     val.type = ValueType::Boolean;
//     val.bool_value = src;
//     return val;
//   }

//   Value Value::make_nil() {
//     Value val{ValueType::Nil};
//     return val;
//   }

//   Value Value::make_undefined() {
//     Value val{ValueType::Undefined};
//     return val;
//   }

//   Value Value::make_builtin_fn(const char* name) {
//     Value val;
//     if (strlen(name) > 7) {
//       return make_undefined();
//     } else {
//       val.type = ValueType::BuiltinFunction;
//       strcpy(val.short_str, name);
//     }
//     return val;
//   }
// }