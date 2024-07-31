#include "mti_630/mti_630.hpp"
#include "mti_630/data_packet_parser.hpp"
#include "mti_630/xbus_packet.hpp"
#include "utility/queue.hpp"
#include <iostream>
#include <iomanip>
#include <boost/asio.hpp>
#include <stdexcept>
#include <string_view>

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

mti_630::~mti_630()
{
    if (port.is_open())
        port.close();
}

char mti_630::read_byte()
{
    char byte;
    boost::asio::read(port, boost::asio::buffer(&byte, 1));

    if (!port.is_open())
        throw std::runtime_error("Failed to read from the serial port.");

    return byte;
}

extern queue<Xbus> imu_data_queue;
[[noreturn]] void mti_630::work (){
    XbusPacket packet{};
    while (true) {
        try
        {
            char byte = this->read_byte();
            packet.feedByte(static_cast<uint8_t>(byte));
            if (packet.isPacketComplete())
            {
                if (packet.validateChecksum())
                {
                    Xbus xbusData;
                    std::vector<uint8_t> rawData = packet.getRawData();
                    DataPacketParser::parseDataPacket(rawData, xbusData);
                    imu_data_queue.push(xbusData);
                    packet.reset();
                }
                else
                {
                    std::cerr << "Checksum invalid!" << std::endl;
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
  