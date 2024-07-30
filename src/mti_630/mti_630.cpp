#include "mti_630/mti_630.hpp"

#include "iostream"
#include "mti_630/mti_buffer.hpp"

mti_630::mti_630 (std::string_view port_name, std::uint32_t baud_rate,
                  boost::asio::serial_port_base::parity::type parity,
                  boost::asio::serial_port_base::stop_bits::type stop_bits,
                  boost::asio::serial_port_base::character_size char_size)
    : service{}, port{ service }
{
  try
    {
      port.open (port_name.data ());
      port.set_option (boost::asio::serial_port_base::baud_rate (baud_rate));
      port.set_option (boost::asio::serial_port_base::parity (parity));
      port.set_option (boost::asio::serial_port_base::stop_bits (stop_bits));
      port.set_option (char_size);
    }
  catch (const std::exception &e)
    {

      // clang-format off                                     flush the buffer
      std::cerr << "err opening serial port := " << e.what () << std::endl;
      // clang-format on
    }
}

mti_630::~mti_630 ()
{
  if (port.is_open ())
    {
      port.close ();
    }
}

[[nodiscard]] std::uint8_t
mti_630::read_byte ()
{
  std::uint8_t byte{ 0 };
  boost::asio::read (port, boost::asio::buffer (&byte, 1));
  return byte;
}

[[noreturn]] void
mti_630::work ()
{
  mti_buffer buffer{};
  while (true)
    {
      auto byte = this->read_byte ();
      buffer.feed_byte (byte);
    }
}
