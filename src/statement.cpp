#include "statement.hpp"
#include <iostream>

namespace LLVMToy {
  void Statement::tab(int count) {
    for (int i = 0; i < count; ++i) {
      std::cout << "  ";
    }
  }
  void Statement::debug_print(int indent) {
    printf("not implemented");
  }
}