#pragma once

#include "Token.h"
#include <string>

class Visitor;
class Expr {
public:
  virtual std::string accept(Visitor *visitor) = 0;
};

class Binary : public Expr {
public:
  Expr *m_Left;
  Token *m_Op;
  Expr *m_Right;

public:
  Binary(Expr *left, Token *op, Expr *right)
      : m_Left(left), m_Op(op), m_Right(right){};
  std::string accept(Visitor *visitor);
};

class Unary : public Expr {
public:
  Expr *m_Left;
  Token *m_Op;

public:
  Unary(Token *op, Expr *left) : m_Left(left), m_Op(op){};
  std::string accept(Visitor *visitor);
};

class Literal : public Expr {
public:
  int m_Value;

public:
  Literal(int value) : m_Value(value){};
  std::string accept(Visitor *visitor);
};

class Grouping : public Expr {
public:
  Expr *m_Expr;

public:
  Grouping(Expr *expr) : m_Expr(expr){};
  std::string accept(Visitor *visitor);
};

class Visitor {
public:
  virtual std::string visitBinary(Binary *binary) = 0;
  virtual std::string visitLiteral(Literal *literal) = 0;
  virtual std::string visitGrouping(Grouping *grouping) = 0;
  virtual std::string visitUnary(Unary *unary) = 0;
};