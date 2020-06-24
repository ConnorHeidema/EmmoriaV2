#ifndef __MOUSE_UTILS__
#define __MOUSE_UTILS__

#include "util/Mediamap.hpp"
#include "util/Entitymap.hpp"

#include <unordered_map>
#include <string>
#include <experimental/filesystem>

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

// 	MouseUtils();
// 	bool BufferedLeftClick();

// private:
// 	int m_currentLeftClick;
// 	static int const s_kBufferedLeftClickFrameCap
};

#endif