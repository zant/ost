#include "Ost.h"
#include "AstPrinter.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  std::shared_ptr<Token> t{new Token{TokenType::Star, "*", "", 1}};
  std::shared_ptr<Literal> l{new Literal{1}};
  std::shared_ptr<Literal> l2{new Literal{1}};
  Binary b{l, t, l};
  std::shared_ptr<Binary> sb{new Binary {l, t, l}};
  Binary b2{sb, t, l};
  AstPrinter printer{};
  printer.print(&b2);
}
