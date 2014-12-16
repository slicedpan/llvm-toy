#ifndef SRC_PARSER_HPP
#define SRC_PARSER_HPP

#include <vector>
#include <string>

#include "namespace.hpp"
#include "token.hpp"
#include "abstract_syntax_tree.hpp"

namespace LLVMToy {
  class Parser {
    public:
      void parse(const vector<Token>& tokens);
      AbstractSyntaxTree& get_abstract_syntax_tree();
    private:
      AbstractSyntaxTree ast;
  };
}

#endif