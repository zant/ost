#include "ost/parser.h"

// Expr Parser::expression() {
//   return this->equality();
// }

// Expr Parser::equality() {
//   return this->comparison();
// }

// Expr Parser::comparison() {
//   return this->term();
// }

// Expr Parser::term() {
//   return this->factor();
// }

// Expr Parser::factor() {
//   return this->unary();
// }

// Expr Parser::unary() {
//   return this->primary();
// }

Literal Parser::primary() {
  Literal e(1);
  return e;
}