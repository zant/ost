#include "Lox.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "Usage: jlox <script>" << std::endl;
  } else if (argc == 2) {
    Lox::runFile(argv[1]);
  } else {
    Lox::runPrompt();
  }
}