#pragma once

#include <string>
#include <variant>

enum class TokenType
{
  // Single char tokens
  LeftParen,
  RightParen,
  LeftBrace,
  RightBrace,
  Comma,
  Dot,
  Minus,
  Plus,
  Semicolon,
  Slash,
  Star,

  // One or two char
  Bang,
  BangEqual,
  Equal,
  EqualEqual,
  Greater,
  GreaterEqual,
  Less,
  LessEqual,

  // Literals
  Identifier,
  String,
  Number,

  // Keywords
  And,
  Class,
  Else,
  False,
  True,
  Function,
  For,
  If,
  Nil,
  Or,
  Print,
  Return,
  Super,
  This,
  Var,
  While,

  LEOF,
};

struct Token
{
  TokenType type;
  std::string lexeme;
  std::variant<std::string, double> literal;
  int line;

  Token(TokenType type, std::string lexeme, std::string literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line){};
  Token(TokenType type, std::string lexeme, double literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line){};
  std::string to_string() { return lexeme + " " + std::to_string(line); }
};