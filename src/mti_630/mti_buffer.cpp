#include "mti_630/mti_buffer.hpp"

[[nodiscard]] bool
mti_buffer::is_buffer_complete () const
{
  if (!is_length_valid)
    {
      return false;
    }

  size_t total_length = 3 + 1 + expected_length + 1;
  return buffer.size () == total_length;
}

[[nodiscard]] std::optional<std::uint8_t>
mti_buffer::compute_checksum () const
{
  if (buffer.size () < 2)
    {
      return std::nullopt;
    }
  std::uint8_t checksum = 0;
  for (size_t i = 1; i < buffer.size (); ++i)
    {
      checksum += buffer[i];
    }
  return checksum;
}

[[nodiscard]] bool
mti_buffer::validate_checksum () const
{
  if (!is_buffer_complete ())
    {
      return false;
    }

  auto checksum = compute_checksum ();
  if (!checksum.has_value ())
    {
      return false;
    }

  return checksum.value () == buffer.back ();
}

void
mti_buffer::reset () noexcept
{
  buffer.clear ();
  is_extended_length = false;
  expected_length = 0;
  is_length_valid = false;
  got_first_byte = false;
  got_second_byte = false;
}

void
mti_buffer::feed_byte (std::uint8_t byte) noexcept
{
  if (buffer.empty () && byte == 0xFA)
    {
      buffer.push_back (byte);
      got_first_byte = true;
      return;
    }

  if (got_first_byte && !got_second_byte)
    {
      if (byte == 0xFF)
        {
          buffer.push_back (byte);
          got_second_byte = true;
        }
      else
        {
          this->reset ();
        }
      return;
    }

  if (got_first_byte && got_second_byte && buffer.size () == 2)
    {
      if (byte == 0x36)
        {
          buffer.push_back (byte);
        }
      else
        {
          reset ();
        }
      return;
    }

  if (got_first_byte && got_second_byte && buffer.size () >= 3)
    {
      buffer.push_back (byte);

      if (buffer.size () == 4)
        {
          expected_length = byte;
          is_length_valid = true;
        }

      if (is_buffer_complete ())
        {
          // COMPLETE MESSAGE LOGIC
          reset ();
        }
    }
}
