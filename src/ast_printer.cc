#include "ost/ast_printer.h"
#include <iostream>
#include <fmt/core.h>

std::string AstPrinter::accept() { return ""; }

template <typename T>
std::string AstPrinter::accept(T arg)
{
  return " " + arg->accept(this);
}

template <typename T, typename... Args>
std::string AstPrinter::parenthesize(std::string lexeme, T first,
                                     Args... args)
{

  std::string text = "(" + lexeme;
  if (lexeme == "grouping")
  {
    text = "(group ";
  }

  text = text + this->accept(first) + this->accept(args...) + ")";
  return text;
};

std::string AstPrinter::format(Expr *expr)
{
  return expr->accept(this);
};

std::string AstPrinter::visit_binary(Binary *binary)
{
  return parenthesize(binary->op->lexeme, binary->left, binary->right);
};

std::string AstPrinter::visit_literal(Literal *literal)
{
  return std::to_string(literal->value);
};

std::string AstPrinter::visit_unary(Unary *unary)
{
  return parenthesize(unary->op->lexeme, unary->left);
};

std::string AstPrinter::visit_grouping(Grouping *grouping)
{
  return parenthesize("grouping", grouping->expr);
};