#ifndef OPERATOR_ACTION_HPP
#define OPERATOR_ACTION_HPP

#include "../value.hpp"
#include "../operator_types.hpp"

namespace LLVMToy {
  namespace OperatorAction {
    Value apply_binary_operator(Types::Operator op, Value left, Value right);
    Value apply_unary_operator(Types::Operator op, Value value);
  }
}

#endif