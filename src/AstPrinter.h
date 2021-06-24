#pragma once

#include "Expr.h"
#include <string>

class AstPrinter : Visitor {
public:
  void print(Expr *expr);
  std::string visitBinary(Binary *binary);
  std::string visitLiteral(Literal *literal);
  std::string parenthesize(Token *token, Expr *arg1, Expr *arg2);
};