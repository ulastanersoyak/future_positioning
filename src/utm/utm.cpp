#include "utm/utm.hpp"
#include "time_and_location/coordinate.hpp"

#include <cmath>
#include <numbers>
#include <string>

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

inline const std::string letters{ "CDEFGHJKLMNPQRSTUVWX" };

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
  this->zone_char_
      = letters.at (static_cast<std::size_t> ((latitude + 80) / 8));
}

std::ostream& operator<<(std::ostream& os, const utm& utm) {
    os << "Easting: " << utm.easting_ << ", "
       << "Northing: " << utm.northing_ << ", "
       << "Zone Number: " << utm.zone_number_ << ", "
       << "Zone Char: " << utm.zone_char_ << ", "
       << "Time: " << utm.time_<<
       "\n";
    return os;
}

[[nodiscard]] std::size_t utm::get_time_diff_sec(const utm &other) const noexcept
{
  return this->time_ - other.time_; 
}

[[nodiscard]] double utm::get_distance(const utm &other) const noexcept
{
  return std::sqrt(std::pow((this->easting_ - other.easting_), 2) + std::pow((this->northing_ - other.northing_), 2)); 
}

[[nodiscard]] direction utm::get_direction (const utm &other) const noexcept
{
   auto EW = (this->easting_ - other.easting_) > 0 ? DIREC::EAST : DIREC::WEST;
   auto NS = (this->northing_ - other.northing_) > 0 ? DIREC::NORTH : DIREC::SOUTH;
   auto hypotenuse = this->get_distance(other);
   auto degree{ 0.0 }; 
   if(NS == DIREC::NORTH){
      degree = std::asin((other.easting_ - this->easting_)  / hypotenuse);
   }
   else
   {
      degree = std::asin((this->northing_ - other.northing_)  / hypotenuse);
   }
   return {NS, EW, degree};
}