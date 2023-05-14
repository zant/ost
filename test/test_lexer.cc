#include <catch2/catch_test_macros.hpp>
#include "ost/lexer.h"
#include <vector>
#include <iostream>
#include <fmt/core.h>
#include <magic_enum.hpp>
#include "ost/utils.h"

TEST_CASE("Lexes one number", "[lex]")
{
  Token a{TokenType::Number, "1", 0, 0, 1, 1};
  Lexer lexer{"1"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
  REQUIRE(scanned_tokens[0].type == a.type);
  REQUIRE(scanned_tokens[0].line == a.line);
  REQUIRE(scanned_tokens[0].start == a.start);
  REQUIRE(scanned_tokens[0].end == a.end);
}

TEST_CASE("Lexes numbers and single char operands", "[lex]")
{
  Token a{TokenType::Number, "1", 1, 0, 1, 1};
  Token b{TokenType::Plus, "+", 1, 1, 2};
  Token c{TokenType::Number, "1", 1, 2, 3, 1};
  Token d{TokenType::LEOF, fmt::format("{}", '\0'), 0, 3, 4};
  Token tokens[]{a, b, c, d};

  Lexer lexer{"1+1"};
  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size(); i++)
  {
    auto lex = scanned_tokens[i].lexeme;
    auto lex_2 = tokens[i].lexeme;
    REQUIRE(scanned_tokens[i].lexeme == tokens[i].lexeme);
    REQUIRE(scanned_tokens[i].type == tokens[i].type);
    REQUIRE(scanned_tokens[i].start == tokens[i].start);
    REQUIRE(scanned_tokens[i].end == tokens[i].end);
  }
}

TEST_CASE("Skips whitespace", "[lex]")
{
  Token a{TokenType::Number, "1", 0, 0, 1, 1};
  Lexer lexer{"1    \t"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
  REQUIRE(scanned_tokens[0].type == a.type);
  REQUIRE(scanned_tokens[0].line == a.line);
}

TEST_CASE("Lexes string wiht multiple numbers and operands properly", "[lex]")
{
  std::string source = "1*1-2 / 1";
  std::string trimmed = trim(source);
  Lexer lexer{source};
  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size() - 1; i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == trimmed.substr(i, 1));
  }
}

TEST_CASE("Lexes maybe comparison", "[lex]")
{
  Token a{TokenType::Equal, "=", 0, 0, 1, "="};
  Lexer lexer{"="};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
}

TEST_CASE("Lexes double comparison", "[lex]")
{
  Token a{TokenType::Equal, "==", 0, 0, 2};
  Lexer lexer{"=="};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == a.lexeme);
}

TEST_CASE("Lexes binary comparison operation", "[lex]")
{
  std::string source = "1<2<1";
  std::string trimmed = trim(source);
  Lexer lexer{source};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  for (size_t i = 0; i < scanned_tokens.size() - 1; i++)
  {
    REQUIRE(scanned_tokens[i].lexeme == trimmed.substr(i, 1));
  }
}

TEST_CASE("Scans string", "[lex]")
{
  Token t{TokenType::String, "\"hola\"", 0, 0, 6, "hola"};
  Lexer lexer{"\"hola\""};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == t.lexeme);
  REQUIRE(scanned_tokens[0].literal == t.literal);
  REQUIRE(scanned_tokens[0].start == t.start);
  REQUIRE(scanned_tokens[0].end == t.end);
}

TEST_CASE("Scans multidigit numbers", "[lex]")
{
  Token t{TokenType::Number, "123123", 0, 0, 6, 123123};
  Lexer lexer{"123123"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == t.lexeme);
  REQUIRE(scanned_tokens[0].literal == t.literal);
  REQUIRE(scanned_tokens[0].start == t.start);
  REQUIRE(scanned_tokens[0].end == t.end);
}

TEST_CASE("Scans keywords", "[lex]")
{
  Token t{TokenType::Identifier, "for", 0, 0, 3};
  Lexer lexer{"for"};

  std::vector<Token> scanned_tokens = lexer.scan_tokens();
  REQUIRE(scanned_tokens[0].lexeme == t.lexeme);
  REQUIRE(scanned_tokens[0].start == t.start);
  REQUIRE(scanned_tokens[0].end == t.end);
}