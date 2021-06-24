#include "AstPrinter.h"
#include "Lox.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {
  // leaky codeeee yayyyy
  AstPrinter().print(new Binary(new Literal(10), new Token(PLUS, "+", "", 1),
                                new Literal(20)));
  // if (argc > 2) {
  //   std::cout << "Usage: jlox <script>" << std::endl;
  // } else if (argc == 2) {
  //   Lox::runFile(argv[1]);
  // } else {
  //   Lox::runPrompt();
  // }
}