#pragma once
#include <string>

struct Ost
{
  inline static bool hadError = false;

  static void runFile(std::string path);
  static void runPrompt();
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);

private:
  static void run(std::string file);
};