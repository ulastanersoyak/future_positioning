#include "utm/utm.hpp"
#include "time_and_location/coordinate.hpp"

#include <cmath>
#include <numbers>

inline constexpr double WGS84_SEMI_MAJOR_AXIS{ 6378137.0 };
inline constexpr double WGS84_FLATTENING{ 1.0 / 298.257223563 };
inline constexpr double ECCENTRICITY_2{
  (2 * WGS84_FLATTENING) - (WGS84_FLATTENING * WGS84_FLATTENING)
};
inline const double ECCENTRICITY{ std::sqrt (ECCENTRICITY_2) };
inline constexpr double SCALE_FACTOR{ 0.9996 };
inline constexpr double FALSE_EASTING{ 500000 };
inline constexpr double FALSE_NORTHING_NORTH{ 0 };
inline constexpr double FALSE_NORTHING_SOUTH{ 10000000 };

utm::utm (const rmc &rmc_) : time_ (rmc_.time_)
{
  double latitude = coordinate_to_decimal (rmc_.latitude_);
  double longitude = coordinate_to_decimal (rmc_.longitude_);

  const auto zone = static_cast<std::uint32_t> (((longitude + 180) / 6) + 1);

  double central_meridian_in_radian
      = ((((zone - 1) * 6) - 180) + 3) * (std::numbers::pi / 180);

  double phi = latitude * (std::numbers::pi / 180);
  double lambda = longitude * (std::numbers::pi / 180);

  double N
      = WGS84_SEMI_MAJOR_AXIS
        / std::sqrt (1 - ECCENTRICITY_2 * std::sin (phi) * std::sin (phi));

  double T = std::tan (phi) * std::tan (phi);
  double C = ECCENTRICITY_2 * std::cos (phi) * std::cos (phi)
             / (1 - ECCENTRICITY_2);

  double A = std::cos (phi) * (lambda - central_meridian_in_radian);

  double M
      = WGS84_SEMI_MAJOR_AXIS
        * ((1 - ECCENTRICITY_2 / 4 - 3 * ECCENTRICITY_2 * ECCENTRICITY_2 / 64
            - 5 * ECCENTRICITY_2 * ECCENTRICITY_2 * ECCENTRICITY_2 / 256)
               * phi
           - (3 * ECCENTRICITY_2 / 8 + 3 * ECCENTRICITY_2 * ECCENTRICITY_2 / 32
              + 45 * ECCENTRICITY_2 * ECCENTRICITY_2 * ECCENTRICITY_2 / 1024)
                 * std::sin (2 * phi)
           + (15 * ECCENTRICITY_2 * ECCENTRICITY_2 / 256
              + 45 * ECCENTRICITY_2 * ECCENTRICITY_2 * ECCENTRICITY_2 / 1024)
                 * std::sin (4 * phi)
           - (35 * ECCENTRICITY_2 * ECCENTRICITY_2 * ECCENTRICITY_2 / 3072)
                 * std::sin (6 * phi));

  double E = FALSE_EASTING
             + SCALE_FACTOR * N
                   * (A + (1 - T + C) * std::pow (A, 3) / 6
                      + (5 - 18 * T + std::pow (T, 2) + 72 * C
                         - 58 * ECCENTRICITY_2)
                            * std::pow (A, 5) / 120);

  double N_value
      = (latitude < 0) ? FALSE_NORTHING_SOUTH : FALSE_NORTHING_NORTH;
  double N_coord = N_value
                   + SCALE_FACTOR
                         * (M - (latitude < 0 ? 10000000 : 0)
                            + N
                                  * (std::pow (A, 2) / 2
                                     + (5 - T + 9 * C) * std::pow (A, 4) / 24
                                     + (61 - 58 * T + std::pow (T, 2))
                                           * std::pow (A, 6) / 720));
  this->easting_ = E;
  this->northing_ = N_coord;
  this->zone_number_ = zone;
}
