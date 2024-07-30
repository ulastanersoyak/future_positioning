#ifndef MTI_630_HPP
#define MTI_630_HPP

#include <boost/asio.hpp>
#include <cstdint>
#include <string_view>

// https://github.com/jiminghe/Xsens_MTi_Serial_Reader
class mti_630
{
  // https://stackoverflow.com/questions/717239/io-service-why-and-how-is-it-used
  boost::asio::io_service service;
  boost::asio::serial_port port;

public:
  mti_630 (std::string_view port_name, std::uint32_t baud_rate,
           boost::asio::serial_port_base::parity::type parity,
           boost::asio::serial_port_base::stop_bits::type stop_bits,
           boost::asio::serial_port_base::character_size char_size);

  mti_630 (mti_630 &&other) = delete;
  mti_630 (const mti_630 &) = delete;
  mti_630 &operator= (mti_630 &&other) = delete;
  mti_630 &operator= (const mti_630 &) = delete;
  ~mti_630 ();

  [[nodiscard]] std::uint8_t read_byte ();
  [[noreturn]] void work ();
};

#endif // !MTI_630_HPP
