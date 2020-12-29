#ifndef __DIALOG_FACADE_COMP__
#define __DIALOG_FACADE_COMP__

#include <string>
#include <list>

/**
 * This component should be added for any dialog which should be shown on screen
 */
struct DialogFacadeComp
{
	std::list<std::string> m_dialogList;
	std::string m_portrait;
};

#endif
