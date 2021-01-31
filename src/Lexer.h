#pragma once
#include <string>
#include <vector>

#include "Token.h"

class Lexer {
private:
  std::string m_Source;
  std::vector<Token> m_Tokens{};
  int m_Start = 0;
  int m_Current = 0;
  int m_Line = 0;

private:
  bool isAtEnd();
  void scanToken();
  char advance();
  void addToken(TokenType type);
  bool match(char expected);
  char peek();
  char peekNext();
  bool isDigit(char c);
  void string();
  void number();

  template <typename T> void addToken(TokenType type, T literal);

public:
  Lexer(std::string source) : m_Source(source){};
  ~Lexer(){};
  std::vector<Token> scanTokens();
};