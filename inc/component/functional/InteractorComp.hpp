#ifndef __INTERACTOR_COMP__
#define __INTERACTOR_COMP__

#include <list>
#include <string>

/**
 * This component should be added to any entity which may be interacted with. This is the subject of the interaction
 */
struct InteractorComp
{
	std::list<std::string> m_currentInteractablesList;
};

#endif