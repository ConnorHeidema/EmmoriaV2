#ifndef __BUTTON_COMP__
#define __BUTTON_COMP__

#include <string>

/**
 * This component should be added to any entity which acts as a button
 */
struct ButtonComp
{
	std::string m_action;
};

#endif