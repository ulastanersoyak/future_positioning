#include "time_and_location/date.hpp"

bool
operator== (const date &dt1, const date &dt2)
{
  return (dt1.yy == dt2.yy) && (dt1.mm == dt2.mm) && (dt1.dd == dt2.dd);
}
