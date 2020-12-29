#ifndef __MOUSE_UTILS__
#define __MOUSE_UTILS__

class MouseUtils
{
public:
	static bool IsCollisionDetected_(
		int const& left,
		int const& top,
		int const& width,
		int const& height,
		int const& xMousePosition,
		int const& yMousePosition);
};

#endif