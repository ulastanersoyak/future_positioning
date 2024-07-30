#ifndef MTI_DATA_PACKAGE_HPP
#define MTI_DATA_PACKAGE_HPP

#include "time_and_location/utc.hpp"
#include <array>
#include <numbers>

inline constexpr double rad_to_degree = 180.0 / std::numbers::pi;
inline constexpr double minus_half_pi = -std::numbers::pi / 2;
inline constexpr double half_pi = std::numbers::pi / 2;

struct mti_data_package
{
  std::array<double, 3> euler{ 0.0, 0.0, 0.0 };
  std::array<double, 4> quaternion{ 0.0, 0.0, 0.0, 0.0 };
  std::array<double, 3> acceleration{ 0.0, 0.0, 0.0 };
  std::array<double, 3> rotation{ 0.0, 0.0, 0.0 };
  std::array<double, 3> velocity{ 0.0, 0.0, 0.0 };
  std::array<double, 3> magnitude{ 0.0, 0.0, 0.0 };
  std::array<double, 2> lat_lon{ 0.0, 0.0 };
  double altitude{ 0.0 };
  utc time{ 0, 0, 0 };

  mti_data_package ();

public:
};

#endif // !MTI_DATA_PACKAGE_HPP
