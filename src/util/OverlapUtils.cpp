#include "util/OverlapUtils.hpp"

bool OverlapUtils::Overlapping(
	Position& rPosition1,
	Size& rSize1,
	Position& rPosition2,
	Size& rSize2)
{
	if (rPosition1.x > rPosition2.x + rSize2.width ||
		rPosition2.x > rPosition1.x + rSize1.width)
	{
		return false;
	}

	if (rPosition1.y > rPosition2.y + rSize2.height ||
		rPosition2.y > rPosition1.y + rSize1.height)
	{
		return false;
	}
	return true;
}
