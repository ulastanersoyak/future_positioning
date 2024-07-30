#include "gps/gps.hpp"
#include "mti_630/mti_630.hpp"
#include "rmc/rmc.hpp"
#include "utm/utm.hpp"

#include <fstream>
#include <iostream>

int
main ()
{
  // clang-format off
    // header,  utc,   fix, latitude  , longitude   ,knot ,,date  ,mode, checksum
    // $GNRMC,072336.00,A,3958.59380,N,03244.28403,E,0.053,,260724,,,A,V*18
  // clang-format on

  gps gps_ ("/dev/serial0", 9600, boost::asio::serial_port_base::parity::none,
            boost::asio::serial_port_base::stop_bits::one,
            boost::asio::serial_port_base::character_size (8));

  mti_630 mti ("/dev/serial0", 115200,
               boost::asio::serial_port_base::parity::none,
               boost::asio::serial_port_base::stop_bits::one,
               boost::asio::serial_port_base::character_size (8));

  gps_.work ();
  mti.work ();
}
