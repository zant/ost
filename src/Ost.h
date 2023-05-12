#pragma once
#include <string>

struct Ost
{
  inline static bool had_error = false;

  static void run_file(std::string path);
  static void run_prompt();
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);

private:
  static void run(std::string file);
};