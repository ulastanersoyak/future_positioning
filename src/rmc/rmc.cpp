#include "rmc/rmc.hpp"
#include "time_and_location/parser.hpp"

#include <sstream>
#include <string>
#include <vector>

rmc::rmc (std::string_view nmea_sentence) noexcept (false)
{
  std::stringstream ss (nmea_sentence.data ());
  std::string token;
  std::vector<std::string> tokens;
  tokens.reserve (11);
  //$GNRMC 072332.00 A 3958.59385 N 03244.28443 E 0.062  260724   A V*1F
  while (std::getline (ss, token, ','))
    {
      if (token != "" && token != ",")
        {
          tokens.push_back (token);
        }
    }

  if (tokens.size () != 11)
    {
      throw std::invalid_argument ("insufficient tokens in nmea sentence");
    }

  const auto time = std::get<utc> (parse_date_and_utc (tokens.at (1)));
  const auto latitude
      = parse_coordinate (tokens.at (3).append (tokens.at (4)));
  const auto longitude
      = parse_coordinate (tokens.at (5).append (tokens.at (6)));
  const auto dt = std::get<date> (parse_date_and_utc (tokens.at (8)));

  this->time_ = time;
  this->latitude_ = latitude;
  this->longitude_ = longitude;
  this->speed_over_ground_knot_ = std::stof (tokens.at (7));
  this->date_ = dt;
  this->checksum = static_cast<std::uint8_t> (std::stoi (
      tokens.at (10).substr (tokens.at (10).size () - 2), nullptr, 16));
  this->fix_status_ = tokens.at (2).at (0);
};
