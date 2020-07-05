#include "util/OverlapUtils.hpp"

#include "util/ApplicationParameters.hpp"

bool OverlapUtils::Overlapping(
	Position& rPosition1,
	Size& rSize1,
	Position& rPosition2,
	Size& rSize2)
{
	if (rPosition1.x - rSize1.width/2 >= rPosition2.x + rSize2.width/2 - ApplicationParameters::k_overlapBuffer ||
		rPosition2.x - rSize2.width/2 >= rPosition1.x + rSize1.width/2 - ApplicationParameters::k_overlapBuffer)
	{
		return false;
	}

	if (rPosition1.y - rSize1.height/2 >= rPosition2.y + rSize2.height/2 - ApplicationParameters::k_overlapBuffer ||
		rPosition2.y - rSize1.height/2 >= rPosition1.y + rSize1.height/2 - ApplicationParameters::k_overlapBuffer)
	{
		return false;
	}
	return true;
}
