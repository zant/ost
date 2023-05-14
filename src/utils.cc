#include "ost/utils.h"
#include <algorithm>

bool find_value(std::vector<char> vec, char value)
{
  auto it = std::find(vec.begin(), vec.end(), value);
  if (it == vec.end())
    return false;
  else
    return true;
}

std::string trim(std::string s)
{
  s.erase(std::remove_if(s.begin(), s.end(), std::isspace), s.end());
  return s;
}