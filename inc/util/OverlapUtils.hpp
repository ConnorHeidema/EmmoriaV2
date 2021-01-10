#ifndef __OVERLAP_UTILS__
#define __OVERLAP_UTILS__
struct Size;
struct Position;

class OverlapUtils
{
public:
	static bool Overlapping(
		Position const& rPosition1,
		Size const& rSize1,
		Position const& rPosition2,
		Size const& rSize2);
private:
	static bool OverlappingOnAxis_(double x1, double x2, int width1, int width2);
};

#endif
