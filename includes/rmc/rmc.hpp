#ifndef RMC_HPP
#define RMC_HPP

#include "time_and_location/coordinate.hpp"
#include "time_and_location/date.hpp"
#include "time_and_location/utc.hpp"

#include <string_view>

class rmc
{
  utc time_;
  coordinate latitude_{};
  coordinate longitude_{};
  float speed_over_ground_knot_{ 0 };
  float course_over_ground_degree_{ 0 };
  date date_;
  std::uint8_t checksum{ 0 };
  char fix_status_{ '_' };

public:
  constexpr explicit rmc (std::string_view nmea_sentence);
};

#endif // !RMC_HPP
