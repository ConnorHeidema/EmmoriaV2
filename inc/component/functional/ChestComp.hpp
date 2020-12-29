#ifndef __CHEST_COMP__
#define __CHEST_COMP__

#include <string>

/**
 * This component should be added to any chest
 */
struct ChestComp
{
	bool m_bOpened;
	std::string m_contents;
	ChestComp() : m_bOpened(false), m_contents("")
	{

	}
};

#endif