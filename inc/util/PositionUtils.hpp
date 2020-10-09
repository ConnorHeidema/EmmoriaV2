#ifndef __POSITION_UTILS__
#define __POSITION_UTILS__

#include "util/Position.hpp"

class PositionUtils
{
public:
	static void CalculateNewPosition(Position& position, double const& speed, double const& angle);
};

#endif