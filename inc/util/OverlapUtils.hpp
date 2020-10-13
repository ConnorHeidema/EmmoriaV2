#ifndef __OVERLAP_UTILS__
#define __OVERLAP_UTILS__

#include "util/Position.hpp"
#include "util/Size.hpp"

class OverlapUtils
{
public:
	static bool Overlapping(Position const& rPosition1, Size const& rSize1, Position const& rPosition2, Size const& rSize2);
};

#endif