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

	static void InteractPlayerCompHealingPadComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
	static void InteractPlayerCompBlobComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
	static void InteractPlayerCompWallComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);

	static std::unordered_map<int, fnEntityInteractor> CreateInteractionFnList();
};


#endif