#include <catch2/catch_test_macros.hpp>
#include "ost/utils.h"

TEST_CASE("Find value bool", "[util]")
{
  std::vector<char> vec{'a', 'b', 'c'};
  bool res = find_value(vec, 'b');
  REQUIRE(res == true);
  std::string a = "1+1";
  std::string b = a.substr(1,1);
  REQUIRE(b == "+");
}

TEST_CASE("Trims string", "[util]")
{
  std::string str = "with spaces and shit";
  REQUIRE(trim(str) == "withspacesandshit");
}
