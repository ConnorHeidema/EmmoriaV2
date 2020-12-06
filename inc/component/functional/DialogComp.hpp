#ifndef __DIALOG_COMP__
#define __DIALOG_COMP__

#include <string>

/**
 * This component should be added for any dialog which should be shown on screen
 */
struct DialogComp
{
	std::string m_action;
	bool m_bOpen;

	DialogComp()
		: m_action("")
		, m_bOpen(false)
	{}
};

#endif
