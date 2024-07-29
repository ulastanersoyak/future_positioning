#ifndef UTM_HPP
#define UTM_HPP

#include "rmc/rmc.hpp"
#include "time_and_location/utc.hpp"

#include <iostream>

class utm
{
  double easting_{ 0 };
  double northing_{ 0 };
  std::uint32_t zone_number_{ 0 };
  char zone_char_{ '_' };
  utc time_{ 0, 0, 0 };

public:
  explicit utm (const rmc &rmc_);
  friend std::ostream& operator<<(std::ostream& os, const utm& utm);
};

#endif // !UTM_HPP
