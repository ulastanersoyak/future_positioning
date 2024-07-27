#ifndef RMC_HPP
#define RMC_HPP

#include "time_and_location/coordinate.hpp"
#include "time_and_location/date.hpp"
#include "time_and_location/utc.hpp"

#include <string_view>

class rmc
{
  utc time_{ 0, 0, 0 };
  coordinate latitude_{};
  coordinate longitude_{};
  float speed_over_ground_knot_{ 0 };
  date date_{};
  std::uint8_t checksum{ 0 };
  char fix_status_{ '_' };

public:
  explicit rmc (std::string_view nmea_sentence) noexcept (false);

  // clang-format off
  rmc (utc time, coordinate lat, coordinate lon, float speed, date d,
       std::uint8_t checksum_, char fix)
      : time_ (time), latitude_ (lat), longitude_ (lon),
        speed_over_ground_knot_ (speed), date_ (d), checksum (checksum_),
        fix_status_ (fix){}
  // clang-format on

  friend bool operator== (const rmc &rmc1, const rmc &rmc2);
};

#endif // !RMC_HPP
