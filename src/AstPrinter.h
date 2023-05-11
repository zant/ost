#pragma once

#include "Expr.h"
#include <string>

class AstPrinter : Visitor
{
public:
  void print(Expr *expr);
  std::string visitBinary(Binary *binary);
  std::string visitLiteral(Literal *literal);
  std::string visitUnary(Unary *unary);
  std::string visitGrouping(Grouping *unary);

  std::string accept();
  template <typename T>
  std::string accept(T arg);
  template <typename T, typename... Args>
  std::string parenthesize(std::string lexeme, T first, Args... args);
};