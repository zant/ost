#pragma once
#include <string>

class Ost {
public:
  static void runFile(std::string path);
  static void runPrompt();
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);

private:
  static void run(std::string file);

public:
  inline static bool hadError = false;
};