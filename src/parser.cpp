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
#include "ast/function_call.hpp"
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
      if (peek().type == Types::Token::RightBrace || peek().type == Types::Token::EndOfFile) {
        break;
      }
      ret.push_back(parse_variable_declaration());
    }
    return ret;
  }

  Statement* Parser::parse_variable_declaration() {
    if (peek().type != Types::Token::KeywordVar) {
      return parse_if_statement();
    }
    consume();
    const Token& id_token = consume_type(Types::Token::Identifier, "Expected valid identifier");
    Expression* expression = nullptr;
    if (peek().type == Types::Token::OperatorEquals) {
      consume();
      expression = parse_expression(ParserPrecedence::Parentheses);
    }
    return new VariableDeclaration(id_token, expression);
  }

  Statement* Parser::parse_if_statement() {
    if (peek().type != Types::Token::KeywordIf) {
      return parse_return_statement();
    }
    consume();
    consume_type(Types::Token::LeftParen, "Expected '(' after if keyword");
    Expression* condition = parse_expression();
    consume_type(Types::Token::RightParen, "Expected ')' after condition in if statement");
    vector<Statement*> body;
    vector<Statement*> else_branch;
    if (peek().type == Types::Token::LeftBrace) {
      consume();
      body = parse_block();
      consume_type(Types::Token::RightBrace, "Expected '}' at end of block");
    } else {
      body.push_back(parse_variable_declaration());
    }
    if (peek().type == Types::Token::KeywordElse) {
      consume();
      switch(peek().type) {
        case(Types::Token::LeftBrace):
          consume();
          else_branch = parse_block();
          consume_type(Types::Token::RightBrace, "Expected '}' at end of block");
          break;
        case(Types::Token::KeywordIf):
          else_branch.push_back(parse_if_statement());
          break;
        default:
          else_branch.push_back(parse_variable_declaration());
      }
    }
    return new IfStatement(condition, body, else_branch);
  }

  const Token& Parser::consume_type(Types::Token type, string error_message) {
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

  Expression* Parser::parse_function_declaration(int max_precedence) {
    if (peek().type != Types::Token::KeywordFunction) {
      return parse_unary_expression(max_precedence);      
    }
    consume();
    Token id_token;
    // Sentinel value
    id_token.type = Types::Token::EndOfFile;
    if (peek().type != Types::Token::LeftParen) {
      id_token = consume_type(Types::Token::Identifier, "Expected valid identifier");
    }
    consume_type(Types::Token::LeftParen, "Expected '('");
    std::vector<Token> arguments;
    if (peek().type != Types::Token::RightParen) {
      for(;;) {
        arguments.emplace_back(consume_type(Types::Token::Identifier, "Expected identifier for function argument"));
        if (peek().type == Types::Token::Comma) {
          consume();
        } else {
          break;
        }
      }
      consume_type(Types::Token::RightParen, "Expected ')' at end of argument list");
    } else {
      consume();
    }
    consume_type(Types::Token::LeftBrace, "Expected function block (missing '{')");
    Expression* ret = new FunctionDeclaration(arguments, parse_block());
    if (id_token.type == Types::Token::Identifier) {
      ret = new Assignment(new VariableReference(id_token), ret);
    }
    consume_type(Types::Token::RightBrace, "Expected '}' at end of function body");
    return ret;
  }

  Statement* Parser::parse_expression_statement() {
    Expression* expression = parse_expression();
    return new ExpressionStatement(expression);
  }

  Statement* Parser::parse_return_statement() {
    if (peek().type != Types::Token::KeywordReturn && peek().type != Types::Token::KeywordReturnEmpty) {
      return parse_expression_statement();
    }
    Token return_token = consume();
    return new ReturnStatement(
      return_token.type == Types::Token::KeywordReturnEmpty ? nullptr : parse_expression()
    );
  }

  Expression* Parser::parse_expression(int max_precedence) {
    Expression* expr = parse_parenthesised_expression(max_precedence);
    Expression* next_expr = nullptr;
    for (;;) {
      const Token& next = peek();
      next_expr = nullptr;
      switch(next.type) {
        case Types::Token::OperatorDivide:
        case Types::Token::OperatorMultiply:
          if (max_precedence > ParserPrecedence::Multiplication) {
            consume();
            next_expr = new BinaryOperator(next, expr, parse_expression(ParserPrecedence::Multiplication));
          }
          break;
        case Types::Token::OperatorMinus:
        case Types::Token::OperatorPlus:
          if (max_precedence > ParserPrecedence::Addition) {
            consume();
            next_expr = new BinaryOperator(next, expr, parse_expression(ParserPrecedence::Addition));
          }
          break;
        case Types::Token::OperatorEquals:
          if (max_precedence >= ParserPrecedence::Assign) {
            if (!expr->assignable()) {
              throw ParserError("Can't assign to this expression");
            }
            consume();
            next_expr = new Assignment(expr, parse_expression(ParserPrecedence::Assign));
          }
          break;
        case Types::Token::OperatorDoubleEquals:
          if (max_precedence > ParserPrecedence::Equality) {
            consume();
            next_expr = new BinaryOperator(next, expr, parse_expression(ParserPrecedence::Equality));
          }
          break;
        case Types::Token::LeftParen:
          consume();
          next_expr = new FunctionCall(expr, parse_argument_expressions());
          consume_type(Types::Token::RightParen, "Expected ')'");
          break;
      }
      if (next_expr == nullptr) {
        break;
      } else {
        expr = next_expr;
      }
    }
    return expr;
  }

  std::vector<Expression*> Parser::parse_argument_expressions() {
    std::vector<Expression*> expressions;
    for (;;) {
      if (peek().type == Types::Token::RightParen || peek().type == Types::Token::EndOfFile) {
        break;
      }
      if (!expressions.empty()) consume_type(Types::Token::Comma, "Expected ',' between arguments");
      expressions.push_back(parse_expression(ParserPrecedence::Parentheses));      
    }
    return expressions;
  }

  Expression* Parser::parse_parenthesised_expression(int max_precedence) {
    if (peek().type != Types::Token::LeftParen) {
      return parse_function_declaration(max_precedence);
    }
    consume();
    Expression* ret = parse_expression(max_precedence);
    consume_type(Types::Token::RightParen, "Expected ')'");
    return ret;
  }

  Expression* Parser::parse_identifier(int max_precedence) {
    const Token& tok = consume_type(Types::Token::Identifier, "Expected identifier");
    return new VariableReference(tok);
  }

  Expression* Parser::parse_literal(int max_precedence) {
    Expression* ret;
    const Token& tok = peek();
    switch (tok.type) {
      case Types::Token::String:
        ret = new StringLiteral(tok);
        break;
      case Types::Token::FloatingPoint:
        ret = new FloatingPointLiteral(tok);
        break;
      case Types::Token::Integer:
        ret = new IntegerLiteral(tok);
        break;
      case Types::Token::Boolean:
        ret = new BooleanLiteral(tok);
        break;
      default:
        return parse_identifier(max_precedence);
    }
    consume();
    return ret;
  }

  Expression* Parser::parse_unary_expression(int max_precedence) {
    if (peek().type != Types::Token::OperatorNot && peek().type != Types::Token::OperatorMinus) {
      return parse_literal(max_precedence);
    }
    return new UnaryOperator(consume(), parse_expression(ParserPrecedence::Unary));
  }

  bool Parser::match(Types::Token token_type) {
    return false;
  }

  const Token& Parser::peek() {
    return tokens[token_index];
  }

  const vector<Statement*>& Parser::get_statements() {
    return statements;
  }

  void Parser::debug_print() {
    for (auto iter = statements.begin(); iter != statements.end(); ++iter) {
      (*iter)->debug_print(0);
    }
  }
}