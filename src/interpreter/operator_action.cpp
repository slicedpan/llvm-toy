#include "operator_action.hpp"
#include <cstring>

namespace LLVMToy {
  namespace OperatorAction {
    const Value undefined_value{ ValueType::Undefined };

    inline Value apply_not(Value value) {
      return Value::make_bool(!value.is_truthy());
    }

    inline Value apply_minus(Value value) {
      switch(value.type) {
        case ValueType::Integer:
          return Value::make_int(-value.int_value);
          break;
        case ValueType::FloatingPoint:
          return Value::make_float(-value.fp_value);
          break;
      }
      return undefined_value;
    }

    inline Value apply_multiplication(Value left, Value right) {
      switch(left.type) {
        case ValueType::Integer:
          if (right.type == ValueType::Integer) {
            return Value::make_int(left.int_value * right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(right.fp_value * left.int_value);
          }
          break;
        case ValueType::FloatingPoint:
          if (right.type == ValueType::Integer) {
            return Value::make_float(left.fp_value * right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(left.fp_value * right.fp_value);
          }
          break;
      }
      return undefined_value;
    }

    inline Value apply_division(Value left, Value right) {
      switch(left.type) {
        case ValueType::Integer:
          if (right.type == ValueType::Integer) {
            return Value::make_int(left.int_value / right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(left.int_value / right.fp_value);
          }
          break;
        case ValueType::FloatingPoint:
          if (right.type == ValueType::Integer) {
            return Value::make_float(left.fp_value / right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(left.fp_value / right.fp_value);
          }
          break;
      }
      return undefined_value;
    }

    inline Value apply_addition(Value left, Value right) {
      switch(left.type) {
        case ValueType::Integer:
          if (right.type == ValueType::Integer) {
            return Value::make_int(left.int_value + right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(right.fp_value + left.int_value);
          }
          break;
        case ValueType::FloatingPoint:
          if (right.type == ValueType::Integer) {
            return Value::make_float(left.fp_value + right.int_value);
          }
          if (right.type == ValueType::FloatingPoint) {
            return Value::make_float(left.fp_value + right.fp_value);
          }
          break;
      }
      return undefined_value;
    }

    inline Value apply_subtraction(Value left, Value right) {
      return apply_addition(left, apply_minus(right));
    }

    inline Value apply_equality(Value left, Value right) {
      if (left.type != right.type)
        return Value::make_bool(false);
      switch (left.type) {
        case ValueType::Integer:
          return Value::make_bool(left.int_value == right.int_value);
          break;
        case ValueType::FloatingPoint:
          return Value::make_bool(left.fp_value == right.fp_value);
          break;
        case ValueType::String:
          return Value::make_bool(!strcmp(left.string_value, right.string_value));
          break;
        default:
          return Value::make_bool(false);
      }      
    }

    Value apply_binary_operator(Types::Operator op, Value left, Value right) {
      switch (op) {
        case Types::Operator::Plus:
          return apply_addition(left, right);
          break;
        case Types::Operator::Minus:
          return apply_subtraction(left, right);
          break;
        case Types::Operator::Multiply:
          return apply_multiplication(left, right);
          break;
        case Types::Operator::Divide:
          return apply_division(left, right);
          break;
        case Types::Operator::DoubleEquals:
          return apply_equality(left, right);
          break;
      }
      return undefined_value;      
    }
    Value apply_unary_operator(Types::Operator op, Value value) {
      switch(op) {
        case Types::Operator::Not:
          return apply_not(value);
          break;
      }
      return undefined_value;
    }
  }
}