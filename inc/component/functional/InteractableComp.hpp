#ifndef __INTERACTABLE_COMP__
#define __INTERACTABLE_COMP__

#include "component/InteractType.hpp"

#include <unordered_set>

struct InteractableComp
{
	std::unordered_set<InteractType_t> m_interactTypeList;
};

#endif