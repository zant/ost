#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.h"

struct Lexer
{
  Lexer(std::string source) : source(source){};
  ~Lexer(){};
  std::vector<Token> scanTokens();

private:
  std::string source;
  std::vector<Token> tokens{};
  int start = 0;
  int current = 0;
  int line = 0;
  std::unordered_map<std::string, TokenType> keywords = {
      {"and", TokenType::AND}, {"class", TokenType::CLASS}, {"else", TokenType::ELSE}, {"false", TokenType::FALSE}, {"for", TokenType::FOR}, {"fun", TokenType::FUN}, {"if", TokenType::IF}, {"nil", TokenType::NIL}, {"or", TokenType::OR}, {"print", TokenType::PRINT}, {"return", TokenType::RETURN}, {"super", TokenType::SUPER}, {"this", TokenType::THIS}, {"true", TokenType::TRUE}, {"var", TokenType::VAR}, {"while", TokenType::WHILE}};

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