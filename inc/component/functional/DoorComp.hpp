#ifndef __DOOR_COMP__
#define __DOOR_COMP__

#include <string>

/**
 * This component should be added to any entity which acts as a button
 */
struct DoorComp
{
	std::string m_action;
	bool m_bOpen;

	DoorComp()
		: m_action("")
		, m_bOpen(false)
	{}
};

#endif
