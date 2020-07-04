#ifndef __OVERLAP_UTILS__
#define __OVERLAP_UTILS__

#include "util/Position.hpp"
#include "util/Size.hpp"

class OverlapUtils
{
public:
	static bool Overlapping(Position& rPosition1, Size& rSize1, Position& rPosition2, Size& rSize2);
};

#endif