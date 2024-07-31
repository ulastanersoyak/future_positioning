#ifndef SERIALHANDLER_HPP
#define SERIALHANDLER_HPP

#include <utility>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/serial_port_base.hpp>

class mti_630 {
    boost::asio::io_service service;
    boost::asio::serial_port port;

public:
    mti_630 (std::string_view port_name, std::uint32_t baud_rate,
            boost::asio::serial_port_base::parity::type parity,
            boost::asio::serial_port_base::stop_bits::type stop_bits,
            boost::asio::serial_port_base::character_size char_size);

    ~mti_630();

    char read_byte();
    [[noreturn]] void work ();
};

#endif  // SERIALHANDLER_HPP
