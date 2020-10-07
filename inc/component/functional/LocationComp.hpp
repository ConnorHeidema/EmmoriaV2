#ifndef __LOCATION_COMP__
#define __LOCATION_COMP__

#include <string>

/**
 * This tag is is used to tell the location of the user
 */
struct LocationComp
{
	std::string area;
	int xLocation;
	int yLocation;
	bool m_bLoaded;
	LocationComp()
		: area("")
		, xLocation(-1)
		, yLocation(-1)
		, m_bLoaded(false)
	{ }
};

#endif