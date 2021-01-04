#include "util/PositionUtils.hpp"
#include "util/OverlapUtils.hpp"

#include "util/Position.hpp"
#include "util/Size.hpp"
#include <math.h>

#include <iostream>

Position PositionUtils::CalculatePositionFromSpeed(Position const& fromOldPosition, double const& speed, double const& angle)
{
	return Position
	{
		fromOldPosition.x + speed * cos(angle),
		fromOldPosition.y + speed * sin(angle)
	};
}

void PositionUtils::CalculateNewPosition(Position& position, double const& speed, double const& angle)
{
	position.x += speed * cos(angle);
	position.y += speed * sin(angle);
}

void PositionUtils::PrintPosition(Position const& position, std::string const& prefix)
{
	if (prefix == "")
	{
		std::cout << "(" << position.x << ", " << position.y << ")" << std::endl;
	}
	else
	{
		std::cout << prefix << ": (" << position.x << ", " << position.y << ")" << std::endl;
	}
}

void PositionUtils::SetObjectToViablePosition(
		Position& positionToRevert,
		Position const& lastPosition,
		Size const& objectSize,
		Position const& wallPosition,
		Size const& wallSize)
{
	Position lastBlobXposition = {lastPosition.x, positionToRevert.y};
	Position lastBlobYposition = {positionToRevert.x, lastPosition.y};

	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastBlobYposition, objectSize))
	{
		positionToRevert.x = lastPosition.x;
	}
	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastBlobXposition, objectSize))
	{
		positionToRevert.y = lastPosition.y;
	}
}