#ifndef __INTERACTOR_COMP__
#define __INTERACTOR_COMP__

#include "component/InteractType.hpp"

#include <unordered_set>
#include <string>

/**
 * This component should be added to any entity which may be interacted with. This is the subject of the interaction
 */
struct InteractorComp
{
	std::unordered_set<InteractType_t> m_interactTypeList;
};

#endif