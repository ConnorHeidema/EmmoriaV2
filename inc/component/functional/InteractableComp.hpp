#ifndef __INTERACTABLE_COMP__
#define __INTERACTABLE_COMP__

#include "component/InteractType.hpp"

#include <list>

struct InteractableComp
{
	std::list<InteractType_t> m_interactTypeList;
};

#endif