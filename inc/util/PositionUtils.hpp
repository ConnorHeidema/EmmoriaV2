#ifndef __POSITION_UTILS__
#define __POSITION_UTILS__

#include <string>

class Position;
class Size;

class PositionUtils
{
public:
	static Position CalculatePositionFromSpeed(Position const& fromOldPosition, double const& speed, double const& angle);
	static void CalculateNewPosition(Position& position, double const& speed, double const& angle);
	static void PrintPosition(Position const& position, std::string const& prefix = "");
	static void SetObjectToViablePosition(
		Position& positionToRevert,
		Position const& lastPositionblobPosition,
		Size const& objectSize,
		Position const& wallPosition,
		Size const& wallSize);
};

#endif