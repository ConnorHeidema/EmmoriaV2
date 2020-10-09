#ifndef __POSITION_UTILS__
#define __POSITION_UTILS__

#include "util/Position.hpp"

#include <string>

class PositionUtils
{
public:
	static void CalculateNewPosition(Position& position, double const& speed, double const& angle);
	static void PrintPosition(Position const& position, std::string const& prefix = "");
};

#endif