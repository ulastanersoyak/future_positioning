#ifndef UTM_HPP
#define UTM_HPP

#include "rmc/rmc.hpp"
#include "time_and_location/directional_info.hpp"
#include "time_and_location/utc.hpp"

#include <cstddef>
#include <iostream>

class utm
{
  double easting_{ 0 };
  double northing_{ 0 };
  std::uint32_t zone_number_{ 0 };
  char zone_char_{ '_' };
  utc time_{ 0, 0, 0 };

public:
  utm () = default;
  explicit utm (const rmc &rmc_);
  [[nodiscard]] std::size_t
  get_time_diff_sec (const utm &other) const noexcept;
  [[nodiscard]] double get_distance (const utm &other) const noexcept;
  [[nodiscard]] directional_info
  get_direction (const utm &other) const noexcept;
  friend std::ostream &operator<< (std::ostream &os, const utm &utm);
};

#endif // !UTM_HPP
