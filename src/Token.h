#pragma once

#include <string>
#include <variant>

enum class TokenType {
  // Single char tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two char
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  LEOF,
};

class Token {
public:
  Token(TokenType type, std::string lexeme, std::string literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line){};
  Token(TokenType type, std::string lexeme, double literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line){};
  std::string toString() { return lexeme + " " + std::to_string(line); }

public:
  TokenType type;
  std::string lexeme;
  std::variant<std::string, double> literal;
  int line;
};