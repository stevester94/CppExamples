#include <string>
#include <iostream>
#include <sstream>
#include <vector>

void ANNOUNCE_SECTION(std::string x)
{
  std::cout << std::endl << "==========" << x << "==========" << std::endl;
}

template<class T>
std::string vectorToStr( std::vector<T> v ) {
  std::stringstream ss;
  ss << "{ ";
  for( const auto it : v ) {
    ss << it << " ";
  }
  ss << "}";

  return ss.str();
}