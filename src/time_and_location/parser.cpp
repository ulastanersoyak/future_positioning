#include "time_and_location/parser.hpp"
#include "time_and_location/utc.hpp"

#include <string>

[[nodiscard]] std::variant<utc, date>
parse_date_and_utc (std::string_view token) noexcept
{
  // clang-format off
  if (token.size () == 6)
    {
      return date{
        static_cast<uint8_t> (std::stoi (std::string(token.substr (0, 2)))),// day
        static_cast<uint8_t> (std::stoi (std::string(token.substr (2, 2)))),// month
        static_cast<uint8_t> (std::stoi (std::string(token.substr (4, 2)))) // year
      };
    }
  return utc{
    static_cast<uint8_t> (std::stoi (std::string(token.substr (0, 2)))),// hour
    static_cast<uint8_t> (std::stoi (std::string(token.substr (2, 2)))),// minute
    static_cast<uint8_t> (std::stoi (std::string(token.substr (4, 2)))) // second
  };
  // clang-format on
}

[[nodiscard]] coordinate
parse_coordinate (std::string_view token) noexcept
{
  // 3958.59177,N - 03244.28792,E
  const auto numeric_part = token.substr (0, token.size () - 2);
  // clang-format off
  const std::uint8_t degree = static_cast<uint8_t> (std::stoi (std::string(((numeric_part.front () != '0') ?
                                                      numeric_part.substr (0, 2) :
                                                      numeric_part.substr (1, 2)) )));
  const double minute
      = std::stod (std::string(((numeric_part.front () != '0')
                        ? numeric_part.substr (2, numeric_part.size () - 2)
                        : numeric_part.substr (3, numeric_part.size () - 3))));
  // clang-format on
  return { .degree = degree, .minute = minute, .indicator = token.back () };
}
