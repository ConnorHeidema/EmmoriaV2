#include "util/MouseUtils.hpp"

bool MouseUtils::IsCollisionDetected_(
	int const& left,
	int const& top,
	int const& width,
	int const& height,
	int const& xMousePosition,
	int const& yMousePosition)
{
	return
		left < xMousePosition &&
		left + width > xMousePosition &&
		top < yMousePosition &&
		top + height > yMousePosition;
}
