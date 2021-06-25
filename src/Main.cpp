#include "AstPrinter.h"
#include "Lox.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {
  // leaky codeeee yayyyy
  Expr *expression =
      new Binary(new Unary(new Token(MINUS, "-", "", 1), new Literal(123)),
                 new Token(STAR, "*", "", 1), new Grouping(new Literal(45)));

  AstPrinter().print(expression);

  // if (argc > 2) {
  //   std::cout << "Usage: jlox <script>" << std::endl;
  // } else if (argc == 2) {
  //   Lox::runFile(argv[1]);
  // } else {
  //   Lox::runPrompt();
  // }
}