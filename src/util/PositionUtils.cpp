#include "util/PositionUtils.hpp"

#include <math.h>

void PositionUtils::CalculateNewPosition(Position& position, double const& speed, double const& angle)
{
	position.x += speed * cos(angle);
	position.y += speed * sin(angle);
}
