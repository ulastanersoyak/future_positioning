#include "gps/gps.hpp"

#include <iostream>

gps::gps (std::string_view port_name, std::uint32_t baud_rate,
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

gps::~gps ()
{
  if (port.is_open ())
    {
      port.close ();
    }
}

std::string
gps::read ()
{
  boost::asio::streambuf buf;
  boost::asio::read_until (port, buf, '\n');
  std::istream is (&buf);
  std::string line;
  std::getline (is, line);
  return line;
}
