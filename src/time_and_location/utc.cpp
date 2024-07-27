#include "time_and_location/utc.hpp"

[[nodiscard]] constexpr utc
utc::operator- (const utc &other) const noexcept
{
  const auto this_seconds = static_cast<std::uint32_t> (
      (this->hour * 3600) + (this->minute * 60) + (this->second));

  const auto other_seconds = static_cast<std::uint32_t> (
      (other.hour * 3600) + (other.minute * 60) + (other.second));

  const uint32_t second_diff = this_seconds - other_seconds;
  const auto hours = static_cast<uint8_t> (second_diff / 3600);
  const auto minutes = static_cast<uint8_t> ((second_diff % 3600) / 60);
  const auto seconds = static_cast<uint8_t> (second_diff % 60);
  return utc{ hours, minutes, seconds };
}
