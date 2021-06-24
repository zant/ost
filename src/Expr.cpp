#include "Expr.h"

std::string Binary::accept(Visitor *visitor) {
  return visitor->visitBinary(this);
}

std::string Literal::accept(Visitor *visitor) {
  return visitor->visitLiteral(this);
}