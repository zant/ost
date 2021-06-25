#include "AstPrinter.h"
#include <iostream>

std::string AstPrinter::accept() { return ""; }

template <typename T> std::string AstPrinter::accept(T arg) {
  return " " + arg->accept(this);
}

template <typename T, typename... Args>
std::string AstPrinter::parenthesize(std::string lexeme, T first,
                                     Args... args) {

  std::string text = "(" + lexeme;
  if (lexeme == "grouping") {
    text = "(group ";
  }

  text = text + this->accept(first) + this->accept(args...) + ")";
  return text;
};

void AstPrinter::print(Expr *expr) {
  std::cout << expr->accept(this) << std::endl;
};

std::string AstPrinter::visitBinary(Binary *binary) {
  return parenthesize(binary->m_Op->lexeme, binary->m_Left, binary->m_Right);
};

std::string AstPrinter::visitLiteral(Literal *literal) {
  return std::to_string(literal->m_Value);
};

std::string AstPrinter::visitUnary(Unary *unary) {
  return parenthesize(unary->m_Op->lexeme, unary->m_Left);
};

std::string AstPrinter::visitGrouping(Grouping *grouping) {
  return parenthesize("grouping", grouping->m_Expr);
};