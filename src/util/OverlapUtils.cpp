#include "util/OverlapUtils.hpp"

#include "util/ApplicationParameters.hpp"

#include "util/Position.hpp"
#include "util/Size.hpp"

bool OverlapUtils::Overlapping(
	Position const& rPosition1,
	Size const& rSize1,
	Position const& rPosition2,
	Size const& rSize2)
{
	return OverlappingOnAxis_(rPosition1.x, rPosition2.x, rSize1.width, rSize2.width) &&
		OverlappingOnAxis_(rPosition1.y, rPosition2.y, rSize1.height, rSize2.height);
}

bool OverlapUtils::OverlappingOnAxis_(double point1, double point2, int length1, int length2)
{
	return !(point1 - length1/2.f >= point2 + length2/2.f - ApplicationParameters::k_overlapBuffer ||
		point2 - length2/2.f >= point1 + length1/2.f + ApplicationParameters::k_overlapBuffer);
}
