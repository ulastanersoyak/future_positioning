#ifndef DIRECTIONAL_INFO_HPP
#define DIRECTIONAL_INFO_HPP

enum class direction : char
{
  NORTH = 'N',
  SOUTH = 'S',
  EAST = 'E',
  WEST = 'W'
};

struct directional_info
{
  direction x{ 'N' };
  direction y{ 'N' };
  double dir_degree{ 0 };
};

#endif // !DIRECTIONAL_INFO_HPP
