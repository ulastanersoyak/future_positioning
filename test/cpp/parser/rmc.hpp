#ifndef RMC_TEST_HPP
#define RMC_TEST_HPP

#include <array>
#include <stdexcept>
#include <string>

#include "rmc/rmc.hpp"

void
rmc_construction_test ()
{
  std::array<std::string, 3> mmea_msgs{
    "$GNRMC_msg,072244.00,A,3958.59794,N,03244.29486,E,0.113,,260724,,,A,V*14",
    "$GNRMC_msg,072318.00,A,3958.59448,N,03244.28742,E,0.115,,260724,,,A,V*12",
    "$GNRMC,072247.00,A,3958.59798,N,03244.29466,E,0.087,,260724,,,A,V*19",
  };
  // clang-format off
std::array<rmc, 3> rmc_msgs{{
    { {7, 22, 44}, {39, 58.59794, 'N'}, {32, 44.29486, 'E'}, 0.113F, {26, 7, 24}, 20, 'A' },
    { {7, 23, 18}, {39, 58.59448, 'N'}, {32, 44.28742, 'E'}, 0.115F, {26, 7, 24}, 18, 'A' },
    { {7, 22, 47}, {39, 58.59798, 'N'}, {32, 44.29466, 'E'}, 0.087F, {26, 7, 24}, 25, 'A' }
  }};
  // clang-format on
  //
  for (std::uint8_t i = 0; i < 3; i++)
    {
      if (rmc_msgs.at (i) != rmc{ mmea_msgs.at (i) })
        {
          throw std::runtime_error ("rmc_construction_test failed");
        }
    }
}

#endif // !RMC_TEST_HPP
