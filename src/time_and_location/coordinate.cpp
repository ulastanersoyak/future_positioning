#include "time_and_location/coordinate.hpp"

#include <algorithm>

bool
operator== (const coordinate &coord1, const coordinate &coord2)
{
  // clang-format off
  return (coord1.indicator == coord2.indicator)
         && ((std::abs (coord1.minute - coord2.minute)
         <= (std::max (std::abs (coord1.minute), 
             std::abs (coord2.minute)) * 0.001)))
         && (coord1.degree == coord2.degree);
  // clang-format on
}
