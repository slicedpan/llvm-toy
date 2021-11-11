#include "parser.hpp"
#include "token.hpp"
#include "expression.hpp"
#include "ast/variable_declaration.hpp"
#include "ast/function_declaration.hpp"
#include "ast/expression_statement.hpp"
#include "ast/string_literal.hpp"
#include "ast/boolean_literal.hpp"
#include "ast/floating_point_literal.hpp"
#include "ast/integer_literal.hpp"
#include "ast/binary_operator.hpp"
#include "ast/unary_operator.hpp"
#include "ast/assignment.hpp"
#include "ast/variable_reference.hpp"
#include "ast/if_statement.hpp"
#include "ast/return_statement.hpp"
#include "parser_error.hpp"

namespace LLVMToy {
  void Parser::parse() {
    statements = parse_block();
  }

  vector<Statement*> Parser::parse_block() {
    vector<Statement*> ret;
    for (;;) {
      if (peek().type == TokenType::RightBrace || peek().type == TokenType::EndOfFile) {
        break;
      }
      ret.push_back(parse_variable_declaration());
    }
    return ret;
  }

  Statement* Parser::parse_variable_declaration() {
    if (peek().type != TokenType::KeywordVar) {
      return parse_function_declaration();
    }
    consume();
    const Token& id_token = consume_type(TokenType::Identifier, "Expected valid identifier");
    Expression* expression = nullptr;
    if (peek().type == TokenType::OperatorEquals) {
      consume();
      expression = parse_expression(ParserPrecedence::Parentheses);
    }
    return new VariableDeclaration(id_token, expression);
  }

  const Token& Parser::consume_type(TokenType type, string error_message) {
    if (peek().type == type) {
      return consume();
    } else {
      throw ParserError(error_message.c_str());
    }
  }

  const Token& Parser::consume() {
    const Token& ret = peek();
    token_index += 1;
    return ret;
  }

  Statement* Parser::parse_function_declaration() {
    if (peek().type != TokenType::KeywordFunction) {
      return parse_expression_statement();      
    }
    consume();
    const Token& id_token = consume_type(TokenType::Identifier, "Expected valid identifier");
    consume_type(TokenType::LeftParen, "Expected '('");
    std::vector<Token> arguments;
    if (peek().type != TokenType::RightParen) {
      for(;;) {
        arguments.emplace_back(consume_type(TokenType::Identifier, "Expected identifier for function argument"));
        if (peek().type == TokenType::Comma) {
          consume();
        } else {
          break;
        }
      }
      consume_type(TokenType::RightParen, "Expected ')' at end of argument list");
    } else {
      consume();
    }
    consume_type(TokenType::LeftBrace, "Expected function block (missing '{')");
    Statement* ret = new FunctionDeclaration(id_token, arguments, parse_block());
    consume_type(TokenType::RightBrace, "Expected '}' at end of function body");
    return ret;
  }

  Statement* Parser::parse_expression_statement() {
    Expression* expression = parse_expression(ParserPrecedence::Parentheses);
    return new ExpressionStatement(expression);
  }

  Expression* Parser::parse_expression(int max_precedence) {
    Expression* expr = parse_parenthesised_expression(max_precedence);
    const Token& next = peek();
    switch(next.type) {
      case TokenType::OperatorDivide:
      case TokenType::OperatorMultiply:
        if (max_precedence >= ParserPrecedence::Multiplication) {
          consume();
          return new BinaryOperator(next, expr, parse_expression(ParserPrecedence::Multiplication));
        }
        break;
      case TokenType::OperatorMinus:
      case TokenType::OperatorPlus:
        if (max_precedence >= ParserPrecedence::Addition) {
          consume();
          return new BinaryOperator(next, expr, parse_expression(ParserPrecedence::Addition));
        }
        break;
      case TokenType::OperatorEquals:
        if (max_precedence >= ParserPrecedence::Assign) {
          if (!expr->assignable()) {
            throw ParserError("Can't assign to this expression");
          }
          consume();
          return new Assignment(expr, parse_expression(ParserPrecedence::Assign));
        }
        break;
    }
    return expr;
  }

  Expression* Parser::parse_parenthesised_expression(int max_precedence) {
    if (peek().type != TokenType::LeftParen) {
      return parse_unary_expression(max_precedence);
    }
    consume();
    Expression* ret = parse_expression(max_precedence);
    consume_type(TokenType::RightParen, "Expected ')'");
    return ret;
  }

  Expression* Parser::parse_identifier(int max_precedence) {
    const Token& tok = consume_type(TokenType::Identifier, "Expected identifier");
    return new VariableReference(tok);
  }

  Expression* Parser::parse_literal(int max_precedence) {
    Expression* ret;
    const Token& tok = peek();
    switch (tok.type) {
      case TokenType::String:
        ret = new StringLiteral(tok);
        break;
      case TokenType::FloatingPoint:
        ret = new FloatingPointLiteral(tok);
        break;
      case TokenType::Integer:
        ret = new IntegerLiteral(tok);
        break;
      case TokenType::Boolean:
        ret = new BooleanLiteral(tok);
        break;
      default:
        return parse_identifier(max_precedence);
    }
    consume();
    return ret;
  }

  Expression* Parser::parse_unary_expression(int max_precedence) {
    if (peek().type != TokenType::OperatorNot && peek().type != TokenType::OperatorMinus) {
      return parse_literal(max_precedence);
    }
    return new UnaryOperator(consume(), parse_expression(ParserPrecedence::Unary));
  }

  bool Parser::match(TokenType token_type) {
    return false;
  }

  const Token& Parser::peek() {
    return tokens[token_index];
  }

  const vector<Statement*> Parser::get_statements() {
    return statements;
  }

  void Parser::debug_print() {
    for (auto iter = statements.begin(); iter != statements.end(); ++iter) {
      (*iter)->debug_print(0);
    }
  }
}