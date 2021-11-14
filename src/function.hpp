#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "statement.hpp"
#include "namespace.hpp"

namespace LLVMToy {
  class Function {
    public:
      Function(const vector<string>& arguments, const vector<Statement*>& body) {
        this->arguments = arguments;
        this->body = body;
      }
      ~Function() {
        for (int i = 0; i < body.size(); ++i) {
          delete body[i];
        }
      }
      const vector<string>& get_arguments(){ return arguments; }
      const vector<Statement*>& get_body(){ return body; }
    private:
      vector<string> arguments;
      vector<Statement*> body;
  };
}

#endif