#ifndef __OVERLAP_UTILS__
#define __OVERLAP_UTILS__
class Size;
class Position;

class OverlapUtils
{
public:
	static bool Overlapping(
		Position const& rPosition1,
		Size const& rSize1,
		Position const& rPosition2,
		Size const& rSize2);
private:
	static bool OverlappingOnAxis_(int x1, int x2, int width1, int width2);
};

#endif
