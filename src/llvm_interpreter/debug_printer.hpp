#ifndef DEBUG_PRINTER_HPP
#define DEBUG_PRINTER_HPP

#include <cstdint>

namespace llvm {
  class Module;
}

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT void lt_debug_print_i1(bool);
extern "C" DLLEXPORT void lt_debug_print_i8(int8_t);
extern "C" DLLEXPORT void lt_debug_print_i32(int32_t);
extern "C" DLLEXPORT void lt_debug_print_i64(int64_t);

void register_debug_functions(llvm::Module*);

#endif