#include "gps/gps.hpp"
#include "mti_630/mti_630.hpp"
#include "utility/queue.hpp"
#include "utm/utm.hpp"
#include "mti_630/data_packet_parser.hpp"
#include <thread>
#include <iostream>


queue<Xbus> imu_data_queue{};

queue<utm> gps_data_queue{};
int
main ()
{
  // clang-format off
  // header,  utc,   fix, latitude  , longitude   ,knot ,,date  ,mode, checksum
  // $GNRMC,072336.00,A,3958.59380,N,03244.28403,E,0.053,,260724,,,A,V*18
  // clang-format on

  //           GPIO 8-9 | 9->tx 8->rx
  gps gps_ ("/dev/ttyAMA4", 9600, boost::asio::serial_port_base::parity::none,
            boost::asio::serial_port_base::stop_bits::one,
            boost::asio::serial_port_base::character_size (8));

  //           GPIO 14-15 | 14->tx 15->rx
  mti_630 mti ("/dev/ttyAMA0", 115200,
               boost::asio::serial_port_base::parity::none,
               boost::asio::serial_port_base::stop_bits::one,
               boost::asio::serial_port_base::character_size (8));

  std::thread gps_thread (&gps::work, &gps_);
  std::thread mti_thread (&mti_630::work, &mti);

  while (true)
    {
      while(gps_data_queue.size() == 0){
        auto imu_data = imu_data_queue.pop();
        std::cout<<"imu buffer size := "<<imu_data_queue.size()<<' '<<imu_data.acc[0]<<'\n';
      }
      auto gps_data = gps_data_queue.pop();
        std::cout<<"gps buffer size := "<<gps_data_queue.size()<<' '<<gps_data<<'\n';
    }
  gps_thread.join ();
  mti_thread.join ();
  return 0;
}