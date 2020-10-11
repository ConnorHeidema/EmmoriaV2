#ifndef __INTERACT_STRING_MAP__
#define __INTERACT_STRING_MAP__

#include "component/InteractType.hpp"

#include <entt/entt.hpp>

#include <unordered_map>
#include <string>
#include <tuple>

using fnEntityInteractor = void(*)(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);

class InteractStringMap
{
public:
	static std::unordered_map<std::string, InteractType_t> s_interactStringToType;
	static std::unordered_map<InteractType_t, std::string> s_interactTypeToString;
	static std::unordered_map<int, fnEntityInteractor> fnInteractionMap;

#include "component/InteractMacro.hpp"
#define INTERACT_DECLARATION(interactor, interactable) \
		static void Interact ## interactor ## Comp ## interactable ## Comp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
ALL_INTERACTIONS(INTERACT_DECLARATION)

#include "component/EndInteractMacro.hpp"

	static std::unordered_map<int, fnEntityInteractor> CreateInteractionFnList();
};


#endif