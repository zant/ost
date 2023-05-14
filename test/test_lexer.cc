#include <catch2/catch_test_macros.hpp>
#include "ost/lexer.h"
#include <vector>
#include <iostream>
#include <fmt/core.h>
#include <magic_enum.hpp>
#include "ost/utils.h"

TEST_CASE("Lexes one number", "[lex]")
{
  Token a{TokenType::Number, "1", 1, 0};
  Lexer lexer{"1"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
  REQUIRE(scanned_tokens[0].type == a.type);
  REQUIRE(scanned_tokens[0].line == a.line);
}

TEST_CASE("Lexes numbers and single char operands", "[lex]")
{
  Token a{TokenType::Number, "1", 1, 0};
  Token b{TokenType::Plus, "+", "+", 0};
  Token c{TokenType::Number, "1", 1, 0};
  Token d{TokenType::LEOF, "", "", 0};
  Token tokens[]{a, b, c, d};

  Lexer lexer{"1+1"};
  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size(); i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == tokens[i].lexeme);
    REQUIRE(scanned_tokens[i].type == tokens[i].type);
  }
}

TEST_CASE("Skips whitespace", "[lex]")
{
  Token a{TokenType::Number, "1", 1, 0};
  Lexer lexer{"1    \t"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
  REQUIRE(scanned_tokens[0].type == a.type);
  REQUIRE(scanned_tokens[0].line == a.line);
}

TEST_CASE("Lexes one number one operand and skips whitespace", "[lex]")
{
  Token a{TokenType::Number, "1", 1, 0};
  Token b{TokenType::Plus, "+", "+", 0};
  Token c{TokenType::LEOF, "", "", 0};
  std::vector<Token> tokens = {a, b, c};
  Lexer lexer{"1 +"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size(); i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == tokens[i].lexeme);
    REQUIRE(scanned_tokens[i].type == tokens[i].type);
    REQUIRE(scanned_tokens[i].line == tokens[i].line);
  }
}

TEST_CASE("Lexes string wiht multiple numbers and operands properly", "[lex]")
{
  std::string source = "1*1-2 / 1";
  std::string trimmed = trim(source);
  Lexer lexer{source};
  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size(); i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == trimmed.substr(i, 1));
  }
}

TEST_CASE("Lexes maybe comparison", "[lex]")
{
  Token a{TokenType::Equal, "=", "=", 0};
  Lexer lexer{"="};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
}

TEST_CASE("Lexes double comparison", "[lex]")
{
  Token a{TokenType::Equal, "==", "", 0};
  Lexer lexer{"=="};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
}

TEST_CASE("Lexes binary comparison operation", "[lex]")
{
  Token a{TokenType::Number, "1", "", 0};
  Token b{TokenType::GreaterEqual, ">=", "", 0};
  Token c{TokenType::Number, "2", "", 0};
  Token d{TokenType::LEOF, "", "", 0};
  std::vector<Token> tokens = {a, b, c, d};

  Lexer lexer{"1>=2"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size(); i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == tokens[i].lexeme);
    REQUIRE(scanned_tokens[i].type == tokens[i].type);
    REQUIRE(scanned_tokens[i].line == tokens[i].line);
  }
}