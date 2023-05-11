#include "Lexer.h"
#include "Ost.h"
#include "Token.h"

#include <iostream>
#include <stdexcept>

std::vector<Token> Lexer::scanTokens() {
  while (!isAtEnd()) {
    m_Start = m_Current;
    scanToken();
  }
  m_Tokens.push_back(Token(LEOF, "", "", m_Line));
  return m_Tokens;
}

bool Lexer::isAtEnd() { return m_Current >= m_Source.length(); }

void Lexer::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd())
        advance();
    } else {
      addToken(SLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    m_Line++;
    break;
  case '"':
    string();
    break;
  default:
    if (isDigit(c)) {
      number();
    } else if (isAlpha(c)) {
      identifier();
    } else {
      Ost::report(m_Line, " [column " + std::to_string(m_Current - 1) + "]",
                  "Unexpected charater.");
    }
    break;
  }
}

bool Lexer::isDigit(char c) {
  if (c >= '0' && c <= '9')
    return true;
  return false;
}

bool Lexer::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

char Lexer::advance() {
  m_Current++;
  return m_Source[m_Current - 1];
}

bool Lexer::match(char expected) {
  if (isAtEnd())
    return false;
  if (m_Source[m_Current] != expected)
    return false;
  m_Current++;
  return true;
}

char Lexer::peek() {
  if (isAtEnd())
    return '\0';
  return m_Source[m_Current];
}

char Lexer::peekNext() {
  if (m_Current + 1 >= m_Source.length())
    return '\0';
  return m_Source[m_Current + 1];
}

void Lexer::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      m_Line++;
    advance();
  }
  if (isAtEnd()) {
    Ost::error(m_Line, "Unterminated string");
    return;
  }
  advance();

  std::string value = m_Source.substr(m_Start + 1, m_Current - 1);
  addToken(STRING, value);
}

void Lexer::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek()))
      advance();
  }

  double value = std::stod(m_Source.substr(m_Start, m_Current));
  addToken(NUMBER, value);
}

void Lexer::addToken(TokenType type) { addToken(type, ""); }

template <typename T> void Lexer::addToken(TokenType type, T literal) {
  std::string text = m_Source.substr(m_Start, m_Current);
  m_Tokens.push_back(Token(type, text, literal, m_Line));
}

// TODO: two consecuent keywords are not treated like so
void Lexer::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  std::string text = m_Source.substr(m_Start, m_Current);
  TokenType type;
  try {
    type = m_Keywords.at(text);
  } catch (const std::out_of_range &e) {
    type = IDENTIFIER;
  }
  addToken(type, text);
}