#include "ast_evaluator.hpp"
#include "operator_action.hpp"
#include "../memory_allocation.hpp"
#include "../function.hpp"

namespace LLVMToy {
  Value ASTEvaluator::pop_value() {
    Value ret = value_stack.back();
    value_stack.pop_back();
    //cout << "popped " << ret.to_string() << " from stack\n";
    return ret;
  }

  void ASTEvaluator::push_value(Value value) {
    value_stack.push_back(value);
    //cout << "pushed " << value.to_string() << " to stack\n";
  }

  Value ASTEvaluator::gather_value(ASTNode* node) {
    node->accept(*this);
    return pop_value();
  }

  Value ASTEvaluator::get_return_value() {
    if (value_stack.empty()) {
      return nil_value;
    }
    return value_stack.back();
  }

  void ASTEvaluator::evaluate(vector<Statement*> statements, Scope* scope) {
    current_scope = scope;
    for (int i = 0; i < statements.size(); ++i) {
      statements[i]->accept(*this);
      if (return_flag) break;
    }
  }

  void ASTEvaluator::visitAssignment(Assignment* assignment) {
    VariableReference* ref = (VariableReference*)assignment->left;
    current_scope->set_variable(ref->name.content, gather_value(assignment->right));
  }

  void ASTEvaluator::visitBinaryOperator(BinaryOperator* binary_operator) {
    Value left_value = gather_value(binary_operator->left);
    Value right_value = gather_value(binary_operator->right);
    push_value(OperatorAction::apply_binary_operator(binary_operator->op, left_value, right_value));
  }

  void ASTEvaluator::visitBooleanLiteral(BooleanLiteral* boolean_literal) {
    push_value(Value::make_bool(boolean_literal->value.content == "true"));
  }

  void ASTEvaluator::visitExpressionStatement(ExpressionStatement* expression_statement) {
    expression_statement->expression->accept(*this);
  }

  void ASTEvaluator::visitFloatingPointLiteral(FloatingPointLiteral* floating_point_literal) {
    Value fp_value;
    fp_value.type = ValueType::FloatingPoint;
    fp_value.fp_value = atof(floating_point_literal->value.content.c_str());
    push_value(fp_value);   
  }

  void ASTEvaluator::visitFunctionCall(FunctionCall* function_call) {
    Value function_value = gather_value(function_call->function);
    // TODO error if function type is not Function
    if (function_value.type != ValueType::Function) {
      cout << "Tried to call a non-function type" << endl;
      return;
    }
    Function* function = function_value.function;
    Scope* child_scope = current_scope->create_child_scope();
    for (int i = 0; i < function->get_arguments().size(); ++i) {
      child_scope->set_variable(function->get_arguments()[i], gather_value(function_call->arguments[i]));
    }
    ASTEvaluator function_call_evaluator;
    function_call_evaluator.evaluate(function->get_body(), child_scope);
    push_value(function_call_evaluator.get_return_value());
    delete child_scope;
  }

  void ASTEvaluator::visitFunctionDeclaration(FunctionDeclaration* function_declaration) {
    vector<string> arguments;
    for (int i = 0; i < function_declaration->arguments.size(); ++i) {
      arguments.push_back(function_declaration->arguments[i].content);
    }
    Function* function = new Function(arguments, function_declaration->body);
    Value function_value;
    function_value.type = ValueType::Function;
    function_value.function = function;
    push_value(function_value);
  }

  void ASTEvaluator::visitIfStatement(IfStatement* if_statement) {
    if (gather_value(if_statement->condition).is_truthy()) {
      ASTEvaluator if_body_evaluator;
      Scope child_scope(current_scope);
      if_body_evaluator.evaluate(if_statement->body, &child_scope);
      if (if_body_evaluator.return_flag) {
        push_value(if_body_evaluator.get_return_value());
        return_flag = true;
      }
    } else {
      if (if_statement->else_branch.empty()) return;
      ASTEvaluator else_branch_evaluator;
      Scope child_scope(current_scope);
      else_branch_evaluator.evaluate(if_statement->else_branch, &child_scope);
      if (else_branch_evaluator.return_flag) {
        push_value(else_branch_evaluator.get_return_value());
        return_flag = true;
      }
    }
  }

  void ASTEvaluator::visitIntegerLiteral(IntegerLiteral* integer_literal) {
    push_value(Value::make_int(atoi(integer_literal->value.content.c_str())));
  }

  void ASTEvaluator::visitReturnStatement(ReturnStatement* return_statement) {
    if (return_statement->expression) {
      push_value(gather_value(return_statement->expression));
    } else {
      push_value(nil_value);
    }
    return_flag = true;
  }

  void ASTEvaluator::visitStringLiteral(StringLiteral* string_literal) {
    push_value(Value::make_string(string_literal->value.content));
  }

  void ASTEvaluator::visitUnaryOperator(UnaryOperator* unary_operator) {
    push_value(OperatorAction::apply_unary_operator(unary_operator->op, gather_value(unary_operator->expression)));
  }

  void ASTEvaluator::visitVariableDeclaration(VariableDeclaration* variable_declaration) {
    if (variable_declaration->initializer) {
      variable_declaration->initializer->accept(*this);
      current_scope->set_variable(variable_declaration->name.content, pop_value());
    } else {
      current_scope->set_variable(variable_declaration->name.content, nil_value);
    }
  }

  void ASTEvaluator::visitVariableReference(VariableReference* variable_reference) {
    push_value(current_scope->lookup_variable(variable_reference->name.content));
  }
}