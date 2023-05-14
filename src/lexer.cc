#include "ost/lexer.h"
#include "ost/ost.h"
#include "ost/token.h"
#include "ost/utils.h"
#include <fmt/core.h>
#include <algorithm>

bool Lexer::is_at_end() { return static_cast<size_t>(current) >= source.length(); }

bool Lexer::is_digit(char c) { return (c >= '0' && c <= '9') ? true : false; }

void Lexer::add_token(TokenType type)
{
  advance();
  tokens.push_back(Token{type, std::string(&source[start], &source[current]), "", 0});
}

std::vector<Token> Lexer::scan_tokens()
{
  while (!is_at_end())
  {
    start = current;
    switch (source[current])
    {
    case '(':
      add_token(TokenType::LeftParen);
      break;
    case ')':
      add_token(TokenType::RightBrace);
      break;
    case '{':
      add_token(TokenType::LeftBrace);
      break;
    case '}':
      add_token(TokenType::RightBrace);
      break;
    case ',':
      add_token(TokenType::Comma);
      break;
    case '.':
      add_token(TokenType::Dot);
      break;
    case '-':
      add_token(TokenType::Minus);
      break;
    case '+':
      add_token(TokenType::Plus);
      break;
    case ';':
      add_token(TokenType::Semicolon);
      break;
    case '*':
      add_token(TokenType::Star);
      break;
    case '!':
      add_token(match_and_advance('=') ? TokenType::BangEqual : TokenType::Bang);
      break;
    case '=':
      add_token(match_and_advance('=') ? TokenType::EqualEqual : TokenType::Equal);
      break;
    case '<':
      add_token(match_and_advance('=') ? TokenType::LessEqual : TokenType::Less);
      break;
    case '>':
      add_token(match_and_advance('=') ? TokenType::GreaterEqual : TokenType::Greater);
      break;
    case '/':
      if (match_and_advance('/'))
      {
        while (peek() != '\n' && !is_at_end())
          advance();
      }
      else
      {
        add_token(TokenType::Slash);
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
      string();
      break;
    default:
      if (is_digit(source[current]))
      {
        add_token(TokenType::Number);
      }
      else if (is_alpha(source[current]))
      {
        identifier();
      }
      else
      {
        advance();
        fmt::println("{}", source.substr(start, current));
        Ost::report(line, " [column " + std::to_string(current - 1) + "]",
                    "Unexpected charater.");
      }
      break;
    }
  };
  tokens.push_back(Token(TokenType::LEOF, "", "", line));
  return tokens;
}

bool Lexer::is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::is_alpha_numeric(char c) { return is_alpha(c) || is_digit(c); }

char Lexer::advance()
{
  current++;
  return source[current - 1];
}

bool Lexer::match_and_advance(char expected)
{
  if (is_at_end())
    return false;
  if (source[current + 1] != expected)
    return false;
  current++;
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

void Lexer::string()
{
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
  advance();

  // std::string value = source.substr(start + 1, current - 1);
  add_token(TokenType::String);
}

void Lexer::number()
{
  while (is_digit(peek()))
    advance();

  if (peek() == '.' && is_digit(peek_next()))
  {
    advance();
    while (is_digit(peek()))
      advance();
  }

  // double value = std::stod(source.substr(start, current));
  // add_token(TokenType::Number, value);
}

// void Lexer::add_token(TokenType type) { add_token(type, ""); }

// template <typename T>
// void Lexer::add_token(TokenType type, T literal)
// {
//   std::string text = source.substr(start, current);
//   tokens.push_back(Token(type, text, literal, line));
// }

void Lexer::identifier()
{
  while (is_alpha_numeric(peek()))
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