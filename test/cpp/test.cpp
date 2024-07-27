#include "parser/parser.hpp"
#include "parser/rmc.hpp"
int
main ()
{
  parse_coordinate_test ();
  parse_date_and_utc_test ();
  rmc_construction_test ();
  return 0;
}
