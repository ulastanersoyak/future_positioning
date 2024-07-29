#include "gps/gps.hpp"
#include "rmc/rmc.hpp"
#include "utm/utm.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

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

    std::ifstream file("/home/ubuntu/gps_location_estimator/test/python/get_data/data.txt");
    std::string line;
    while ( getline(file, line) && (line != ".") ) 
    {

        if (line.find("GNRMC") != std::string::npos)
        {
            try
            {
                utm utm_((rmc(line)));
                std::cout << utm_;
            }
            catch(...)
            {

            }
        }
    }

}
