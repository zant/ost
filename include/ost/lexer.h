#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "ost/token.h"

struct Lexer
{
  Lexer(std::string source) : source(source){}
  ~Lexer(){}
  std::vector<Token> scanTokens();

private:
  std::string source;
  std::vector<Token> tokens{};
  int start = 0;
  int current = 0;
  int line = 0;
  std::unordered_map<std::string, TokenType> keywords = {
      {"and", TokenType::And}, {"class", TokenType::Class}, {"else", TokenType::Else}, {"false", TokenType::False}, {"for", TokenType::For}, {"function", TokenType::Function}, {"if", TokenType::If}, {"nil", TokenType::Nil}, {"or", TokenType::Or}, {"print", TokenType::Print}, {"return", TokenType::Return}, {"super", TokenType::Super}, {"this", TokenType::This}, {"true", TokenType::True}, {"var", TokenType::Var}, {"while", TokenType::While}};

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
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  void identifier();

  template <typename T>
  void addToken(TokenType type, T literal);
};