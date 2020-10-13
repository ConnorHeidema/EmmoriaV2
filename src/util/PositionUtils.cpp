#include "util/PositionUtils.hpp"
#include "util/OverlapUtils.hpp"

#include <math.h>

#include <iostream>

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