#include "time_and_location/utc.hpp"

[[nodiscard]] std::uint32_t
utc::operator- (const utc &other) const noexcept
{
  const auto this_seconds = static_cast<std::uint32_t> (
      (this->hour * 3600) + (this->minute * 60) + (this->second));

  const auto other_seconds = static_cast<std::uint32_t> (
      (other.hour * 3600) + (other.minute * 60) + (other.second));

  return this_seconds - other_seconds;
}

std::ostream &
operator<< (std::ostream &os, const utc &utc)
{
  os << "Hour: " << static_cast<int> (utc.hour) << ", "
     << "Minute: " << static_cast<int> (utc.minute) << ", "
     << "Second: " << static_cast<int> (utc.second);
  return os;
}
