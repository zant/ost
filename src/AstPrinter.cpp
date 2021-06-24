#include "AstPrinter.h"
#include <iostream>

std::string AstPrinter::parenthesize(Token *token, Expr *arg1, Expr *arg2) {
  std::string text = "(";
  return text + token->lexeme + " " + arg1->accept(this) + " " +
         arg2->accept(this) + ")";
};

void AstPrinter::print(Expr *expr) {
  std::cout << expr->accept(this) << std::endl;
};

std::string AstPrinter::visitBinary(Binary *binary) {
  return parenthesize(binary->m_Op, binary->m_Left, binary->m_Right);
};

std::string AstPrinter::visitLiteral(Literal *literal) {
  return std::to_string(literal->m_Value);
};
