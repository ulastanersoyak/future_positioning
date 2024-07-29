#ifndef DIRECTION_HPP
#define DIRECTION_HPP

enum class DIREC : char
{
    NORTH = 'N',
    SOUTH = 'S',
    EAST = 'E',
    WEST = 'W'
};

struct direction
{
    DIREC x{'N'};
    DIREC y{'N'};
    double dir_degree{0};
};

#endif // !DIRECTION_HPP
