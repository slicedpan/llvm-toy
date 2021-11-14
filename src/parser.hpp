#ifndef SRC_PARSER_HPP
#define SRC_PARSER_HPP

#include <vector>
#include <string>

#include "namespace.hpp"
#include "token.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "parser_precedence.hpp"

namespace LLVMToy {
  class Parser {
    public:
      Parser(const vector<Token>& tokens) : tokens(tokens) {}
      void parse();
      const std::vector<Statement*>& get_statements();
      void debug_print();
    private:
      Statement* parse_variable_declaration();
      Statement* parse_function_declaration();
      Statement* parse_statement();
      Statement* parse_return_statement();
      Statement* parse_expression_statement();
      Statement* parse_if_statement();
      vector<Statement*> parse_block();
      Expression* parse_expression() {
        return parse_expression(ParserPrecedence::Parentheses);
      }
      Expression* parse_expression(int);
      Expression* parse_unary_expression(int);
      Expression* parse_binary_expression(int);
      Expression* parse_parenthesised_expression(int);
      Expression* parse_literal(int);
      Expression* parse_identifier(int);
      vector<Expression*> parse_argument_expressions();
      const Token& consume();
      const Token& peek();
      const Token& consume_type(Types::Token, string);
      bool match(Types::Token);
      int token_index = 0;
      const vector<Token>& tokens;
      vector<Statement*> statements;
  };
}

#endif