#include "Ost.h"
#include "Lexer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "magic_enum.hpp"

void Ost::run(std::string source) {
  Lexer lexer = Lexer(source);
  std::vector<Token> tokens = lexer.scanTokens();

  for (Token &token : tokens) {
    std::cout << magic_enum::enum_name(token.type) << std::endl;
  }
}

void Ost::runFile(std::string path) {
  std::ifstream stream(path);
  if (!stream.good())
    std::cout << "File not found: " << path << std::endl;

  std::stringstream sstr;
  sstr << stream.rdbuf();
  run(sstr.str());
  if (hadError)
    exit(65);
}

void Ost::runPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    std::cin >> line;
    if (line.empty())
      break;
    run(line);
    hadError = false;
  }
}

void Ost::error(int line, std::string message) { report(line, "", message); }

void Ost::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << std::to_string(line) << "] Error" << where << ": "
            << message << std::endl;
  hadError = true;
}