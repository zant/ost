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
  // std::vector<Token> scanTokens();

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
  std::unordered_map<char, TokenType> lexemes = {
      {'(', TokenType::LeftParen},
      {')', TokenType::RightParen},
      {'{', TokenType::LeftBrace},
      {'}', TokenType::False},
      {',', TokenType::Comma},
      {'.', TokenType::Dot},
      {'-', TokenType::Minus},
      {'+', TokenType::Plus},
      {';', TokenType::Semicolon},
      {'/', TokenType::Slash},
      {'*', TokenType::Star},
  };
  std::unordered_map<char, TokenType> maybe_comparisons = {
      {'=', TokenType::Equal},
      {'!', TokenType::Bang},
      {'>', TokenType::Greater},
      {'<', TokenType::Less},
  };
  std::unordered_map<std::string, TokenType> comparisons = {
      {"==", TokenType::EqualEqual},
      {"!=", TokenType::BangEqual},
      {">=", TokenType::GreaterEqual},
      {"<=", TokenType::LessEqual},
  };
  std::vector<char>
      whitespace = {
          ' ',
          '\r',
          '\t',
  };

private:
  void add_token(TokenType);
  bool is_at_end();
  char advance();
  bool match_and_advance(char);
  char peek();
  bool is_digit(char);
  void string();
  void number();
  bool is_alpha(char);
  bool is_alpha_numeric(char);
  void identifier();
  char peek_next();
};