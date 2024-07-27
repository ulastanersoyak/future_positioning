#ifndef PARSER_TEST_HPP
#define PARSER_TEST_HPP

#include "time_and_location/parser.hpp"

#include <array>
#include <stdexcept>
#include <string>

// $GNRMC,072244.00,A,3958.59794,N,03244.29486,E,0.113,,260724,,,A,V*14
// $GNRMC,072247.00,A,3958.59798,N,03244.29466,E,0.087,,260724,,,A,V*19
// $GNRMC,072318.00,A,3958.59448,N,03244.28742,E,0.115,,260724,,,A,V*12
void
parse_date_and_utc_test ()
{
  // clang-format off
  const std::array<std::string, 6> tokens{
    "072244.00",
    "031847.00",
    "130101.00",
    "260724",
    "281221",
    "010113"
  };
  // clang-format on

  const std::array<utc, 3> utcs{
    utc{ 7, 22, 44 },
    utc{ 3, 18, 47 },
    utc{ 13, 1, 1 },
  };

  const std::array<date, 3> dates{
    date{ 26, 7, 24 },
    date{ 28, 12, 21 },
    date{ 1, 1, 13 },
  };

  for (std::uint8_t idx = 0; idx < 6; idx++)
    {
      if (tokens[idx].size () == 6)
        {
          const auto dt = std::get<date> (parse_date_and_utc (tokens[idx]));
          if (dt != dates[idx % 3])
            {
              throw std::runtime_error (
                  "date_utc parser failed on date parsing");
            }
        }
      else
        {
          const auto u = std::get<utc> (parse_date_and_utc (tokens[idx]));
          if (u != utcs[idx % 3])
            {
              throw std::runtime_error (
                  "date_utc parser failed on utc parsing");
            }
        }
    }
}

void
parse_coordinate_test ()
{
  // clang-format off
  const std::array<std::string, 6> tokens{ 
    "3958.59247,N", 
    "03244.28792,E",
    "3958.59770,N",
    "03244.29596,E",
    "3958.59787,N",
    "03244.29493,E",
  };
  // clang-format on
  const std::array<coordinate, 6> coords{
    coordinate{ .degree = 39, .minute = 58.59247, .indicator = 'N' },
    coordinate{ .degree = 32, .minute = 44.28792, .indicator = 'E' },
    coordinate{ .degree = 39, .minute = 58.59770, .indicator = 'N' },
    coordinate{ .degree = 32, .minute = 44.29596, .indicator = 'E' },
    coordinate{ .degree = 39, .minute = 58.59787, .indicator = 'N' },
    coordinate{ .degree = 32, .minute = 44.29493, .indicator = 'E' }
  };

  for (std::uint8_t idx = 0; idx < 6; idx++)
    {
      if (parse_coordinate (tokens[idx]) != coords[idx])
        {
          throw std::runtime_error ("coordinate parser test  failed");
        }
    }
}

#endif // !PARSER_TEST_HPP
