#ifndef DATE_HPP
#define DATE_HPP

#include <cstdint>
struct date
{
  std::uint8_t dd{ 0 };
  std::uint8_t mm{ 0 };
  std::uint8_t yy{ 0 };
};

bool operator== (const date &dt1, const date &dt2);

#endif // !DATE_HPP
