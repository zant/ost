#pragma once

#include "Token.h"
#include <string>

// Make visitor class available
struct Visitor;
struct Expr {
  virtual std::string accept(Visitor *visitor) = 0;
};

struct Binary : public Expr {
  Expr *m_Left;
  Token *m_Op;
  Expr *m_Right;

  Binary(Expr *left, Token *op, Expr *right)
      : m_Left(left), m_Op(op), m_Right(right){};
  std::string accept(Visitor *visitor);
};

struct Unary : public Expr {
  Expr *m_Left;
  Token *m_Op;

  Unary(Token *op, Expr *left) : m_Left(left), m_Op(op){};
  std::string accept(Visitor *visitor);
};

struct Literal : public Expr {
  int m_Value;

  Literal(int value) : m_Value(value){};
  std::string accept(Visitor *visitor);
};

struct Grouping : public Expr {
  Expr *m_Expr;

  Grouping(Expr *expr) : m_Expr(expr){};
  std::string accept(Visitor *visitor);
};


// Define Visitor class
struct Visitor {
  virtual std::string visitBinary(Binary *binary) = 0;
  virtual std::string visitLiteral(Literal *literal) = 0;
  virtual std::string visitGrouping(Grouping *grouping) = 0;
  virtual std::string visitUnary(Unary *unary) = 0;
};