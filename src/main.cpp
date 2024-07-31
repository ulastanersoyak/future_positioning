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

  //           GPIO 14-15 | 14->tx 15->rx
  gps gps_ ("/dev/ttyAMA0", 9600, boost::asio::serial_port_base::parity::none,
            boost::asio::serial_port_base::stop_bits::one,
            boost::asio::serial_port_base::character_size (8));

  //           GPIO 8-9 | 9->tx 8->rx
  mti_630 mti ("/dev/ttyAMA4", 115200,
               boost::asio::serial_port_base::parity::none,
               boost::asio::serial_port_base::stop_bits::one,
               boost::asio::serial_port_base::character_size (8));

  std::thread gps_thread (&gps::work, &gps_);
  std::thread mti_thread (&mti_630::work, &mti);

  utm future_utm{};
  utm current_utm{};
  utm prev_utm{};
  bool is_first_package{ true };
  double distance{ 0.0 };
  double time_diff { 0.0 };
  directional_info direct {};
  double estimated_speed_ms { 0.0 };
  while (true)
    {
      while(gps_data_queue.size() == 0){
        auto imu_data = imu_data_queue.pop();
      }
      current_utm = gps_data_queue.pop();
      if (is_first_package) [[unlikely]]
      {
        prev_utm = current_utm;
        is_first_package = false;
      }
      distance = current_utm.get_distance (prev_utm);
      time_diff = current_utm.get_time_diff_sec (prev_utm);
      direct = current_utm.get_direction (prev_utm);
      estimated_speed_ms = distance / static_cast<double> (time_diff);
      prev_utm = current_utm;
    }
  gps_thread.join ();
  mti_thread.join ();
  return 0;
}