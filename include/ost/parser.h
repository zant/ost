#pragma once

#include "ost/expr.h"
#include <string>
#include <vector>

struct Parser
{
  std::shared_ptr<Expr> parse();
  Parser(std::vector<Token> tokens) : tokens(tokens) {}
  ~Parser() {}

private:
  std::vector<Token> tokens{};
  int current = 0;

private:
  std::shared_ptr<Expr> expression();
  std::shared_ptr<Expr> equality();
  std::shared_ptr<Expr> comparison();
  std::shared_ptr<Expr> term();
  std::shared_ptr<Expr> factor();
  std::shared_ptr<Expr> unary();
  std::shared_ptr<Expr> primary();
  Token advance();
  Token peek();
  bool match(TokenType);
  bool is_at_end();
};