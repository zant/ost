#include "ost/ost.h"
#include "ost/lexer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "magic_enum.hpp"

void Ost::run(std::string source) {
  Lexer lexer = Lexer(source);
  std::vector<Token> tokens = lexer.scan_tokens();

  for (Token &token : tokens) {
    std::cout << magic_enum::enum_name(token.type) << std::endl;
  }
}

void Ost::run_file(std::string path) {
  std::ifstream stream(path);
  if (!stream.good())
    std::cout << "File not found: " << path << std::endl;

  std::stringstream sstr;
  sstr << stream.rdbuf();
  run(sstr.str());
  if (had_error)
    exit(65);
}

void Ost::run_prompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    std::cin >> line;
    if (line.empty())
      break;
    run(line);
    had_error = false;
  }
}

void Ost::error(int line, std::string message) { report(line, "", message); }

void Ost::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << std::to_string(line) << "] Error" << where << ": "
            << message << std::endl;
  had_error = true;
}