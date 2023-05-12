#include "Lexer.h"
#include "Ost.h"
#include "Token.h"

#include <iostream>
#include <stdexcept>

std::vector<Token> Lexer::scanTokens()
{
  while (!isAtEnd())
  {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::LEOF, "", "", line));
  return tokens;
}

bool Lexer::isAtEnd() { return current >= source.length(); }

void Lexer::scanToken()
{
  char c = advance();
  switch (c)
  {
  case '(':
    addToken(TokenType::LeftParen);
    break;
  case ')':
    addToken(TokenType::RightBrace);
    break;
  case '{':
    addToken(TokenType::LeftBrace);
    break;
  case '}':
    addToken(TokenType::RightBrace);
    break;
  case ',':
    addToken(TokenType::Comma);
    break;
  case '.':
    addToken(TokenType::Dot);
    break;
  case '-':
    addToken(TokenType::Minus);
    break;
  case '+':
    addToken(TokenType::Plus);
    break;
  case ';':
    addToken(TokenType::Semicolon);
    break;
  case '*':
    addToken(TokenType::Star);
    break;
  case '!':
    addToken(match('=') ? TokenType::BangEqual : TokenType::Bang);
    break;
  case '=':
    addToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
    break;
  case '<':
    addToken(match('=') ? TokenType::LessEqual : TokenType::Less);
    break;
  case '>':
    addToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
    break;
  case '/':
    if (match('/'))
    {
      while (peek() != '\n' && !isAtEnd())
        advance();
    }
    else
    {
      addToken(TokenType::Slash);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    string();
    break;
  default:
    if (isDigit(c))
    {
      number();
    }
    else if (isAlpha(c))
    {
      identifier();
    }
    else
    {
      Ost::report(line, " [column " + std::to_string(current - 1) + "]",
                  "Unexpected charater.");
    }
    break;
  }
}

bool Lexer::isDigit(char c)
{
  if (c >= '0' && c <= '9')
    return true;
  return false;
}

bool Lexer::isAlpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

char Lexer::advance()
{
  current++;
  return source[current - 1];
}

bool Lexer::match(char expected)
{
  if (isAtEnd())
    return false;
  if (source[current] != expected)
    return false;
  current++;
  return true;
}

char Lexer::peek()
{
  if (isAtEnd())
    return '\0';
  return source[current];
}

char Lexer::peekNext()
{
  if (current + 1 >= source.length())
    return '\0';
  return source[current + 1];
}

void Lexer::string()
{
  while (peek() != '"' && !isAtEnd())
  {
    if (peek() == '\n')
      line++;
    advance();
  }
  if (isAtEnd())
  {
    Ost::error(line, "Unterminated string");
    return;
  }
  advance();

  std::string value = source.substr(start + 1, current - 1);
  addToken(TokenType::String, value);
}

void Lexer::number()
{
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext()))
  {
    advance();
    while (isDigit(peek()))
      advance();
  }

  double value = std::stod(source.substr(start, current));
  addToken(TokenType::Number, value);
}

void Lexer::addToken(TokenType type) { addToken(type, ""); }

template <typename T>
void Lexer::addToken(TokenType type, T literal)
{
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, literal, line));
}

// TODO: two consecuent keywords are not treated like so
void Lexer::identifier()
{
  while (isAlphaNumeric(peek()))
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
  addToken(type, text);
}