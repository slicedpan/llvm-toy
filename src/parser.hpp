#ifndef SRC_PARSER_HPP
#define SRC_PARSER_HPP

#include <vector>
#include <string>

#include "abstract_syntax_tree.hpp"

namespace LLVMToy {
  class Parser {
    public:
      void parse(const std::vector<std::string>& tokens);
    private:
      AbstractSyntaxTree ast;
  };
}

#endif