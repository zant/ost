#include "ost/lexer.h"
#include "ost/ost.h"
#include "ost/token.h"
#include "ost/utils.h"
#include <fmt/core.h>
#include <algorithm>

template <typename T>
void Lexer::add_token(TokenType type, T literal) { tokens.push_back(Token{type, std::string(&source[start], &source[current]), 0, start, current, literal}); }

void Lexer::add_token(TokenType type) { tokens.push_back(Token{type, std::string(&source[start], &source[current]), 0, start, current}); }

void Lexer::consume_token(TokenType type)
{
  advance();
  add_token(type);
}

template <typename T>
void Lexer::consume_token(TokenType type, T literal)
{
  advance();
  add_token(type, literal);
}

void Lexer::scan_token(char c)
{
  switch (c)
  {
  case '(':
    consume_token(TokenType::LeftParen);
    break;
  case ')':
    consume_token(TokenType::RightBrace);
    break;
  case '{':
    consume_token(TokenType::LeftBrace);
    break;
  case '}':
    consume_token(TokenType::RightBrace);
    break;
  case ',':
    consume_token(TokenType::Comma);
    break;
  case '.':
    consume_token(TokenType::Dot);
    break;
  case '-':
    consume_token(TokenType::Minus);
    break;
  case '+':
    consume_token(TokenType::Plus);
    break;
  case ';':
    consume_token(TokenType::Semicolon);
    break;
  case '*':
    consume_token(TokenType::Star);
    break;
  case '!':
    consume_token(match_and_advance('=') ? TokenType::BangEqual : TokenType::Bang);
    break;
  case '=':
    consume_token(match_and_advance('=') ? TokenType::EqualEqual : TokenType::Equal);
    break;
  case '<':
    consume_token(match_and_advance('=') ? TokenType::LessEqual : TokenType::Less);
    break;
  case '>':
    consume_token(match_and_advance('=') ? TokenType::GreaterEqual : TokenType::Greater);
    break;
  case '/':
    if (match_and_advance('/'))
    {
      while (peek() != '\n' && !is_at_end())
        advance();
    }
    else
    {
      consume_token(TokenType::Slash);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    advance();
    break;
  case '\n':
    line++;
    advance();
    break;
  case '"':
    consume_string();
    break;
  default:
    if (is_digit(source[current]))
    {
      consume_number();
    }
    else if (is_alpha(source[current]))
    {
      consume_identifier();
    }
    else
    {
      advance();
      Ost::report(line, " [column " + std::to_string(current - 1) + "]",
                  "Unexpected charater.");
    }
    break;
  }
}

std::vector<Token> Lexer::scan_tokens()
{
  while (!is_at_end())
  {
    start = current;
    scan_token(source[current]);
  };
  consume_eof();
  return tokens;
}

void Lexer::consume_eof() {
  start = current;
  consume_token(TokenType::LEOF);
}

bool Lexer::is_at_end() { return static_cast<size_t>(current) >= source.length(); }

bool Lexer::is_digit(char c) { return (c >= '0' && c <= '9') ? true : false; }

bool Lexer::is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::is_alphanumeric(char c) { return is_alpha(c) || is_digit(c); }

void Lexer::advance()
{
  current++;
}

bool Lexer::match_and_advance(char expected)
{
  if (is_at_end())
    return false;
  if (source[current + 1] != expected)
    return false;

  advance();
  return true;
}

char Lexer::peek()
{
  if (is_at_end())
    return '\0';
  return source[current];
}

char Lexer::peek_next()
{
  if (static_cast<size_t>(current + 1) >= source.length())
    return '\0';
  return source[current + 1];
}

void Lexer::consume_string()
{
  // Start quote
  advance();
  while (peek() != '"' && !is_at_end())
  {
    if (peek() == '\n')
      line++;
    advance();
  }
  if (is_at_end())
  {
    Ost::error(line, "Unterminated string");
    return;
  }
  // End quote
  advance();

  std::string value = std::string(&source[start + 1], &source[current - 1]);
  add_token(TokenType::String, value);
}

void Lexer::consume_number()
{
  while (is_digit(peek()))
    advance();

  if (peek() == '.' && is_digit(peek_next()))
  {
    advance();
    while (is_digit(peek()))
      advance();
  }

  double value = std::stod(std::string(&source[start], &source[current]));
  add_token(TokenType::Number, value);
}

void Lexer::consume_identifier()
{
  while (is_alphanumeric(peek()))
    advance();

  std::string text = source.substr(start, current);
  TokenType type;
  try
  {
    type = keywords.at(text);
  }
  catch (const std::out_of_range &e)
  {
    type = TokenType::Identifier;
  }
  add_token(type);
}