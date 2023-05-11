#pragma once

#include "Expr.h"
#include <string>

class Parser : Visitor
{
public:
  void parse(Expr *expr){};
  std::string visitBinary(Binary *binary){};
  std::string visitUnary(Unary *unary){};
  std::string visitLiteral(Literal *literal){};
  std::string visitGrouping(Grouping *grouping){};
};