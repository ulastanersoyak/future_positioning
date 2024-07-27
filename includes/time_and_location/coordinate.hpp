#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <cmath>
#include <cstdint>

struct coordinate
{
  std::uint8_t degree{ 0 };
  double minute{ 0 };
  char indicator{ '_' };
};

double coordinate_to_decimal (const coordinate &coord);
bool operator== (const coordinate &coord1, const coordinate &coord2);

#endif // !COORDINATE_HPP
