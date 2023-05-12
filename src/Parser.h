#pragma once

#include "Expr.h"
#include <string>
#include <vector>

struct Parser
{
  Parser(std::vector<Token> tokens) : m_Tokens(tokens){};
  ~Parser(){};

private:
  std::vector<Token> m_Tokens{};
  // int m_Current = 0;

private:
  // Expr expression();
  // Expr equality();
  // Expr comparison();
  // Expr term();
  // Expr factor();
  // Expr unary();
  Literal primary();
};