#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "ost/token.h"

struct Lexer
{
  Lexer(std::string source) : source(source) {}
  ~Lexer() {}
  std::vector<Token> scan_tokens();
  static bool is_digit(char);
  static bool is_alpha(char);
  static bool is_alphanumeric(char);

private:
  std::string source;
  std::vector<Token> tokens{};
  int start = 0;
  int current = 0;
  int line = 0;
  std::unordered_map<std::string, TokenType> keywords = {
      {"and", TokenType::And},
      {"class", TokenType::Class},
      {"else", TokenType::Else},
      {"false", TokenType::False},
      {"for", TokenType::For},
      {"function", TokenType::Function},
      {"if", TokenType::If},
      {"nil", TokenType::Nil},
      {"or", TokenType::Or},
      {"print", TokenType::Print},
      {"return", TokenType::Return},
      {"super", TokenType::Super},
      {"this", TokenType::This},
      {"true", TokenType::True},
      {"var", TokenType::Var},
      {"while", TokenType::While},
  };

private:
  void scan_token(char c);
  void add_token(TokenType);
  template <typename T>
  void add_token(TokenType, T);
  void consume_token(TokenType);
  template <typename T>
  void consume_token(TokenType, T);
  void consume_string();
  void consume_number();
  void consume_identifier();
  void consume_eof();
  bool is_at_end();
  void advance();
  bool match_and_advance(char);
  char peek();
  char peek_next();
};