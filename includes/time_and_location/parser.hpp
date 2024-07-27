#ifndef PARSER_HPP
#define PARSER_HPP

#include "time_and_location/coordinate.hpp"
#include "time_and_location/date.hpp"
#include "time_and_location/utc.hpp"

#include <string_view>
#include <variant>

[[nodiscard]] std::variant<utc, date>
parse_date_and_utc (std::string_view token) noexcept;

[[nodiscard]] coordinate parse_coordinate (std::string_view token) noexcept;

#endif // !PARSER_HPP
