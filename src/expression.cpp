#include "expression.hpp"
#include <cstdio>

namespace LLVMToy {
  void Expression::debug_print(int indent) {
    printf("not implemented\n");
  }

  void Expression::tab(int indent) {
    for (int i = 0; i < indent; ++i) {
      printf("  ");
    }
  }
}