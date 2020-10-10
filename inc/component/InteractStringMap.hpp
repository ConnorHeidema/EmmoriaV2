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
	static void InteractWallInteractorCompWallComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
	static void InteractArrowCompBlobComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
	static void InteractPlayerCompHoleComp(entt::registry& rReg, entt::entity& rinteractorEntity, entt::entity& rinteractableEntity);
	static void InteractBlobCompHoleComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity);
	static void InteractDepressableCompWeightComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity);
	static void InteractOpenableCompDepressableComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity);

	static std::unordered_map<int, fnEntityInteractor> CreateInteractionFnList();
};


#endif