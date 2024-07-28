#ifndef GPS_HPP
#define GPS_HPP

#include <boost/asio.hpp>
#include <string_view>

class gps
{
  // https://stackoverflow.com/questions/717239/io-service-why-and-how-is-it-used
  boost::asio::io_service service;
  boost::asio::serial_port port;

public:
  gps (std::string_view port_name, std::uint32_t baud_rate,
       boost::asio::serial_port_base::parity::type parity,
       boost::asio::serial_port_base::stop_bits::type stop_bits,
       boost::asio::serial_port_base::character_size char_size);

  gps (gps &&other) = delete;
  gps (const gps &) = delete;
  gps &operator= (gps &&other) = delete;
  gps &operator= (const gps &) = delete;
  ~gps ();

  std::string read ();
};

#endif // GPS_HPP
