#include "ast_printer.hpp"
#include <sstream>

namespace LLVMToy {
  ASTPrinter::ASTPrinter() {
  }

  void ASTPrinter::print(const vector<Statement*>& statements) {
    for (int i = 0; i < statements.size(); ++i) {
      statements[i]->accept(*this);
      cout << pop_string();
    }
  }

  string ASTPrinter::pop_string() {
    string ret = string_stack.back();
    string_stack.pop_back();
    return ret;
  }

  void ASTPrinter::push_string(const string& str) {
    string_stack.push_back(str);
  }

  string ASTPrinter::gather_outputs(const vector<Statement*>& statements) {
    std::stringstream ss;
    if (statements.empty()) {
      ss << pad(string("<empty>"));
    }
    for (int i = 0; i < statements.size(); ++i) {
      statements[i]->accept(*this);
      ss << pad(pop_string());
    }
    return ss.str();
  }

  string ASTPrinter::gather_outputs(const vector<Expression*>& expressions) {
    std::stringstream ss;
    if (expressions.empty()) {
      ss << pad(string("<empty>"));
    }
    for (int i = 0; i < expressions.size(); ++i) {
      expressions[i]->accept(*this);
      ss << pad(pop_string());
    }
    return ss.str();
  }

  string ASTPrinter::gather_output(Expression* expression) {
    if (expression) {
      expression->accept(*this);
      return pad(pop_string());
    }
    return pad("<null>");
  }

  string ASTPrinter::gather_output(Statement* statement) {
    if (statement) {
      statement->accept(*this);
      return pad(pop_string());
    }
    return pad("<null>");
  }

  string ASTPrinter::pad(const string& src) {
    std::stringstream input_stream(src);
    std::stringstream output_stream;
    std::string line;

    while (std::getline(input_stream, line, '\n')) {
      output_stream << "  " << line << endl;
    }
    return output_stream.str();
  }

  void ASTPrinter::visitAssignment(Assignment* assignment) {
    std::stringstream ss;    
    ss << "ASSIGNMENT\nleft:\n" << gather_output(assignment->left);
    ss << "right:\n" << gather_output(assignment->right); 
    push_string(ss.str());
  }

  void ASTPrinter::visitBinaryOperator(BinaryOperator* binary_operator) {
    std::stringstream ss;    
    ss << "BINARY_OPERATOR(" << Types::OperatorNames.at(binary_operator->op) << ")\nleft:\n";
    ss << gather_output(binary_operator->left) << "right:\n";
    ss << gather_output(binary_operator->right); 
    push_string(ss.str());
  }

  void ASTPrinter::visitBooleanLiteral(BooleanLiteral* boolean_literal) {
    push_string(boolean_literal->get_token().content);
  }

  void ASTPrinter::visitExpressionStatement(ExpressionStatement* expression_statement) {
    std::stringstream ss;
    ss << "EXPR_STMT\n" << "expression:\n" << gather_output(expression_statement->expression);
    push_string(ss.str());
  }

  void ASTPrinter::visitFloatingPointLiteral(FloatingPointLiteral* floating_point_literal) {
    std::stringstream ss;
    ss << floating_point_literal->value << " (fp)";
    push_string(ss.str());
  }

  void ASTPrinter::visitFunctionCall(FunctionCall* function_call) {
    std::stringstream ss;
    ss << "FUNCTION_CALL\n" << "function:\n" << gather_output(function_call->function);
    ss << "arguments:\n";
    ss << gather_outputs(function_call->arguments);
    push_string(ss.str());
  }

  void ASTPrinter::visitFunctionExpression(FunctionExpression* function_expression) {
    std::stringstream ss;
    ss << "FUNCTION_EXPR (";
    for (int i = 0; i < function_expression->arguments.size(); ++i) {
      if (i > 0)
        ss << ", ";
      ss << function_expression->arguments[i].content;
    }
    ss << ")\n" << "body:\n";
    ss << gather_outputs(function_expression->body);
    push_string(ss.str());
  }

  void ASTPrinter::visitIfStatement(IfStatement* if_statement) {
    std::stringstream ss;
    ss << "IF_STMT\n" << "condition:\n" << gather_output(if_statement->condition) << "body:\n";
    ss << gather_outputs(if_statement->body);
    ss << "else_branch:\n";
    ss << gather_outputs(if_statement->else_branch);
    push_string(ss.str());
  }

  void ASTPrinter::visitIntegerLiteral(IntegerLiteral* integer_literal) {
    std::stringstream ss;
    ss << integer_literal->value << " (int)";
    push_string(ss.str());
  }

  void ASTPrinter::visitReturnStatement(ReturnStatement* return_statement) {
    std::stringstream ss;
    ss << "RETURN_STMT\n" << "expression:\n" << gather_output(return_statement->expression);
    push_string(ss.str());
  }

  void ASTPrinter::visitStringLiteral(StringLiteral* string_literal) {
    push_string(string_literal->value);
  }

  void ASTPrinter::visitUnaryOperator(UnaryOperator* unary_operator) {
    std::stringstream ss;
    ss << "UNARY_OPERATOR(" << Types::OperatorNames.at(unary_operator->op) << ")\nexpression:\n";
    ss << gather_output(unary_operator->expression);
    push_string(ss.str());
  }

  void ASTPrinter::visitVariableDeclaration(VariableDeclaration* variable_declaration) {
    std::stringstream ss;
    if (variable_declaration->is_closure) {
      ss << "CLOSURE_VARIABLE_DECL(";
    } else {
      ss << "VARIABLE_DECL(";
    }
    ss << variable_declaration->name << ")\n";
    ss << "initializer:\n" << gather_output(variable_declaration->initializer);
    push_string(ss.str());
  }

  void ASTPrinter::visitVariableReference(VariableReference* variable_reference) {
    std::stringstream ss;
    if (variable_reference->is_closure) {
      ss << "CLOSURE_VAR_REF(" << variable_reference->name << ")\n";
    } else {
      ss << "VAR_REF(" << variable_reference->name << ")\n";  
    } 
    push_string(ss.str());
  }
}