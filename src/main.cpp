#include "utm/utm.hpp"
#include <rmc/rmc.hpp>

int
main ()
{
  // clang-format off
  // header,  utc,   fix, latitude  , longitude   ,knot ,,date  ,mode, checksum
  // $GNRMC,072336.00,A,3958.59380,N,03244.28403,E,0.053,,260724,,,A,V*18
  // clang-format on

  rmc r{
    "$GNRMC,072332.00,A,3958.59385,N,03244.28443,E,0.062,,260724,,,A,V*1F"
  };
  utm u{ r };
  return 0;
}
