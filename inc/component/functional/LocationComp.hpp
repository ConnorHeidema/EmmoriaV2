#ifndef __LOCATION_COMP__
#define __LOCATION_COMP__

#include <string>
#include <memory>

/**
 * This tag is is used to tell the location of the user
 */
struct LocationComp
{
	std::string area;
	int xLocation;
	int yLocation;
	bool m_bLoaded;
	int xSpawnLocation;
	int ySpawnLocation;
	std::string music;
	LocationComp()
		: area("")
		, xLocation(-1)
		, yLocation(-1)
		, m_bLoaded(false)
		, xSpawnLocation(-1)
		, ySpawnLocation(-1)
		, music("")
	{ }
};

#endif