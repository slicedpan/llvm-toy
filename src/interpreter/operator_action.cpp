#include "operator_action.hpp"
#include <cstring>

namespace LLVMToy {
  namespace OperatorAction {
    const Value undefined_value{ ValueType::Undefined };

    inline Value apply_not(Value value) {
      return Value::make_bool(!value.is_truthy());
    }

    inline Value apply_minus(Value value) {
      switch(value.get_type()) {
        case ValueType::FloatingPoint:
          return Value::make_number(-value.float_value);
          break;
      }
      return undefined_value;
    }

    inline Value apply_multiplication(Value left, Value right) {
      return Value::make_number(left.float_value * right.float_value);
    }

    inline Value apply_division(Value left, Value right) {
      return Value::make_number(left.float_value / right.float_value);
    }

    inline Value apply_addition(Value left, Value right) {
      return Value::make_number(left.float_value + right.float_value);
    }

    inline Value apply_subtraction(Value left, Value right) {
      return Value::make_number(left.float_value - right.float_value);
    }

    inline Value apply_equality(Value left, Value right) {
      return Value::make_bool(left.uint_value == right.uint_value);
    }

    Value apply_binary_operator(Types::Operator op, Value left, Value right) {
      if (left.get_type() == ValueType::FloatingPoint && right.get_type() == ValueType::FloatingPoint) {
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