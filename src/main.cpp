#include "gps/gps.hpp"
#include "rmc/rmc.hpp"
#include "utm/utm.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

int
main ()
{
  // clang-format off
    // header,  utc,   fix, latitude  , longitude   ,knot ,,date  ,mode, checksum
    // $GNRMC,072336.00,A,3958.59380,N,03244.28403,E,0.053,,260724,,,A,V*18
  // clang-format on

  // gps serial("/dev/serial0", 9600,
  //         boost::asio::serial_port_base::parity::none,
  //         boost::asio::serial_port_base::stop_bits::one,
  //         boost::asio::serial_port_base::character_size(8));

  // // std::size_t line_no = 0;
  // while (true)
  // {
  //     try
  //     {
  //         std::string line;
  //         while (true)
  //         {
  //             line = serial.read();
  //             if (!line.empty())
  //             {
  //                 if (line.find("GNRMC") != std::string::npos)
  //                 {
  //                     utm utm_((rmc(line)));
  //                 }
  //             }
  //         }
  //     }
  //     catch (const std::exception &e)
  //     {
  //         std::cerr << "error: " << e.what() << std::endl;
  //     }
  // }

  std::ifstream file (
      "/home/ubuntu/gps_location_estimator/test/python/get_data/data.txt");
  std::string line;
  utm current{};
  utm prev{};
  bool is_first_package{ true };
  while (getline (file, line))
    {
      if (line.find ("GNRMC") != std::string::npos)
        {
          try
            {
              current = utm{ rmc{ line } };
              if (is_first_package) [[unlikely]]
                {
                  prev = current;
                  is_first_package = false;
                }
              auto distance = current.get_distance (prev);
              auto time_diff = current.get_time_diff_sec (prev);
              [[maybe_unused]] auto direct = current.get_direction (prev);
              [[maybe_unused]] auto estimated_speed_ms
                  = distance / static_cast<double> (time_diff);
              prev = current;
            }
          catch (...)
            {
            }
        }
    }
}
