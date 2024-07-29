#ifndef UTC_HPP
#define UTC_HPP

#include <compare>
#include <cstdint>

#include <iostream>

class utc
{
  std::uint8_t hour{ 0 };
  std::uint8_t minute{ 0 };
  std::uint8_t second{ 0 };

public:
  utc () = default;
  // clang-format off
  constexpr utc (std::uint8_t hour_, std::uint8_t minute_, std::uint8_t second_)
      : hour{ hour_ }, minute{ minute_ }, second{ second_ } {}
  // clang-format on

  [[nodiscard]] auto operator<=> (const utc &other) const noexcept
      = default;

  [[nodiscard]] std::uint32_t operator- (const utc &other) const noexcept;

  friend std::ostream& operator<<(std::ostream& os, const utc& utc);
};

#endif // !UTC_HPP
