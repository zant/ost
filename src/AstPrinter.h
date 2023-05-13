#pragma once

#include "Expr.h"
#include <string>

struct AstPrinter : Visitor
{
  std::string format(Expr *expr);
  std::string visit_binary(Binary *binary);
  std::string visit_literal(Literal *literal);
  std::string visit_unary(Unary *unary);
  std::string visit_grouping(Grouping *unary);

  std::string accept();
  template <typename T>
  std::string accept(T arg);
  template <typename T, typename... Args>
  std::string parenthesize(std::string lexeme, T first, Args... args);
};