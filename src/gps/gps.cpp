#include "gps/gps.hpp"
#include "rmc/rmc.hpp"
#include "utm/utm.hpp"
#include "utility/queue.hpp"

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

[[nodiscard]] std::string
gps::read ()
{
  boost::asio::streambuf buf;
  boost::asio::read_until (port, buf, '\n');
  std::istream is (&buf);
  std::string line;
  std::getline (is, line);
  return line;
}
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>         
#include <chrono> 

extern queue<utm> gps_data_queue;
[[noreturn]] void
gps::work ()
{
  std::string file_path = "../../test/python/get_data/data.txt";
  std::ifstream file (file_path);
  std::string line;
  while (true)
    {
      //line = this->read ();
      //if (!line.empty ())
      if (getline (file, line))
        {
          if (line.find ("GNRMC") != std::string::npos)
            {
              try{

              utm utm_ ((rmc (line)));
              gps_data_queue.push(utm_);
              }
              catch(...){
                gps_data_queue.push(utm{});
              }
            }
          std::this_thread::sleep_for (std::chrono::milliseconds(200));
        }
    }
}
