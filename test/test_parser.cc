#include <catch2/catch_test_macros.hpp>
#include "ost/lexer.h"
#include "ost/ast_printer.h"
#include "ost/parser.h"

TEST_CASE("Parses", "[parser]")
{
  Lexer l{"1 + 1 * 1 + 1"};
  std::vector<Token> tokens = l.scan_tokens();
  for (auto &val : tokens) {
    fmt::println("{}", val.to_string());
  }

  Parser p{tokens};
  std::shared_ptr<Expr> expr = p.parse();

  AstPrinter printer{};
  auto str = printer.format(expr.get());
  fmt::println("{}", str);
}