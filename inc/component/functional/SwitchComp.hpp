#ifndef __SWITCH_COMP__
#define __SWITCH_COMP__

#include <string>

/**
 * This component should be added to any entity which acts as a button
 */
struct SwitchComp
{
	std::string m_action;
	bool m_bPressed;
	SwitchComp()
		: m_action("")
		, m_bPressed(false)
	{}
};

#endif