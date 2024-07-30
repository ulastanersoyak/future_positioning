#ifndef MTI_BUFFER_HPP
#define MTI_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

class mti_buffer
{
  std::vector<std::uint8_t> buffer;
  std::size_t expected_length{ 0 };
  bool is_extended_length{ false };
  bool is_length_valid{ false };
  bool got_first_byte{ false };
  bool got_second_byte{ false };

public:
  void reset () noexcept;
  [[nodiscard]] bool validate_checksum () const;

  [[nodiscard]] std::optional<std::uint8_t> compute_checksum () const;
  [[nodiscard]] bool is_buffer_complete () const;
  void feed_byte (std::uint8_t byte) noexcept;
};

#endif // !MTI_BUFFER_HPP
