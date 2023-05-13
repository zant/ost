#include <catch2/catch_test_macros.hpp>
#include "ost/ast_printer.h"
#include <thread>

TEST_CASE("Returns formatted", "[formated]")
{
    std::shared_ptr<Token> t{new Token{TokenType::Star, "*", "", 1}};
    std::shared_ptr<Literal> l{new Literal{1}};
    std::shared_ptr<Literal> l2{new Literal{2}};
    std::shared_ptr<Binary> sb{new Binary{l, t, l}};
    Binary *b{new Binary{sb, t, l2}};

    AstPrinter printer{};
    auto str = printer.format(b);

    REQUIRE(str == "(* (* 1 1) 2)");
}