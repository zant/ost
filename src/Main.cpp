#include "Ost.h"
#include "AstPrinter.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  Token t{TokenType::PLUS, "+", "", 1};
  Literal l{1};
  Binary b{&l, &t, &l};
  auto printer = AstPrinter{};
  printer.print(&b);
}
