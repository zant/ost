#include "ost/parser.h"

std::shared_ptr<Expr> Parser::expression()
{
  return this->equality();
}

std::shared_ptr<Expr> Parser::equality()
{
  std::shared_ptr<Expr> e = this->comparison();
  if (match(TokenType::EqualEqual))
  {
    std::shared_ptr<Token> op{new Token(peek())};
    advance();
    std::shared_ptr<Expr> right{new Binary{e, op, Parser::equality()}};
    e = right;
  }
  return e;
}

std::shared_ptr<Expr> Parser::comparison()
{
  std::shared_ptr<Expr> e = this->term();
  if (match(TokenType::Equal) || match(TokenType::LessEqual) || match(TokenType::Greater) || match(TokenType::GreaterEqual))
  {
    std::shared_ptr<Token> op{new Token(peek())};
    advance();
    std::shared_ptr<Expr> right{new Binary{e, op, Parser::comparison()}};
    e = right;
  }
  return e;
}

std::shared_ptr<Expr> Parser::term()
{
  std::shared_ptr<Expr> e = this->factor();
  if (match(TokenType::Plus) || match(TokenType::Minus))
  {
    std::shared_ptr<Token> op{new Token(peek())};
    advance();
    std::shared_ptr<Expr> right{new Binary{e, op, Parser::term()}};
    e = right;
  }
  return e;
}

std::shared_ptr<Expr> Parser::factor()
{
  std::shared_ptr<Expr> e = this->unary();
  if (match(TokenType::Star) || match(TokenType::Slash))
  {
    std::shared_ptr<Token> op{new Token(peek())};
    advance();
    std::shared_ptr<Expr> right{new Binary{e, op, Parser::term()}};
    e = right;
  }
  return e;
}

std::shared_ptr<Expr> Parser::unary()
{
  if (match(TokenType::Bang) || match(TokenType::Minus))
  {
    std::shared_ptr<Token> op{new Token(peek())};
    advance();
    std::shared_ptr<Expr> left{new Unary{op, this->primary()}};
    return left;
  }
  return this->primary();
}

std::shared_ptr<Expr> Parser::primary()
{
  std::shared_ptr<Literal> l{new Literal{advance()}};
  return l;
}

std::shared_ptr<Expr> Parser::parse()
{
  return this->expression();
}

Token Parser::advance()
{
  return tokens[current++];
}

Token Parser::peek()
{
  return tokens[current];
}

bool Parser::match(TokenType type)
{
  return (peek().type == type) ? true : false;
}

bool Parser::is_at_end()
{
  return (static_cast<size_t>(current) >= tokens.size()) ? true : false;
}