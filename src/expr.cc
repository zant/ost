#include "ost/expr.h"

std::string Binary::accept(Visitor *visitor)
{
  return visitor->visit_binary(this);
}

std::string Literal::accept(Visitor *visitor)
{
  return visitor->visit_literal(this);
}

std::string Unary::accept(Visitor *visitor)
{
  return visitor->visit_unary(this);
}

std::string Grouping::accept(Visitor *visitor)
{
  return visitor->visit_grouping(this);
}