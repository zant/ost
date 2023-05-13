#pragma once

#include "ost/token.h"
#include <string>
#include <fmt/core.h>

// Make visitor class available
struct Visitor;
struct Expr
{
  virtual std::string accept(Visitor *visitor) = 0;
  virtual ~Expr(){};
};

struct Binary : public Expr
{
  std::shared_ptr<Expr> left;
  std::shared_ptr<Token> op;
  std::shared_ptr<Expr> right;

  Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> op, std::shared_ptr<Expr> right)
      : left{left}, op{op}, right{right} {};
  std::string accept(Visitor *visitor);
};

struct Unary : public Expr
{
  std::shared_ptr<Expr> left;
  std::shared_ptr<Token> op;

  Unary(std::shared_ptr<Token> op, std::shared_ptr<Expr> left) : left{left}, op{op}{};
  std::string accept(Visitor *visitor);
};

struct Literal : public Expr
{
  int value;

  Literal(int value) : value{value}{};
  std::string accept(Visitor *visitor);
};

struct Grouping : public Expr
{
  std::shared_ptr<Expr> expr;

  Grouping(std::shared_ptr<Expr> expr) : expr{expr}{};
  std::string accept(Visitor *visitor);
};

// Define Visitor class
struct Visitor
{
  virtual std::string visit_binary(Binary *binary) = 0;
  virtual std::string visit_literal(Literal *literal) = 0;
  virtual std::string visit_grouping(Grouping *grouping) = 0;
  virtual std::string visit_unary(Unary *unary) = 0;
};
