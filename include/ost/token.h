#pragma once

#include <string>
#include <variant>
#include <fmt/core.h>
#include <magic_enum.hpp>

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

using TokenLiteral = std::variant<std::string, double>;

struct Token
{
  TokenType type;
  std::string lexeme;
  int line;
  int start;
  int end;
  TokenLiteral literal = {};

  Token(TokenType type, std::string lexeme, int line, int start, int end, std::string literal)
      : type(type), lexeme(lexeme), line(line), start(start), end(end), literal(literal) {}
  Token(TokenType type, std::string lexeme, int line, int start, int end, double literal)
      : type(type), lexeme(lexeme), line(line), start(start), end(end), literal(literal) {}
  Token(TokenType type, std::string lexeme, int line, int start, int end)
      : type(type), lexeme(lexeme), line(line), start(start), end(end) {}
  Token() {}

  std::string to_string()
  {
    std::string token_string = fmt::format("token: {}\nline: {}\ntype: {}\nstart: {}\nend: {}\n", lexeme, std::to_string(line), magic_enum::enum_name(type), start, end);
    return token_string;
  }
};