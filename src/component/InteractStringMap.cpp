#include "component/InteractStringMap.hpp"

#include "component/functional/HealthComp.hpp"

#include <iostream>

#include "entity/EntityMacro.hpp"
#define INTERACT_STRING_TO_TYPE_MAPPING(name) { #name , InteractType_t:: name##_t },
#define INTERACT_TYPE_TO_STRING_MAPPING(name) { InteractType_t:: name##_t, #name },

std::unordered_map<std::string, InteractType_t> InteractStringMap::s_interactStringToType =
{
	ALL_TAG_MACRO(INTERACT_STRING_TO_TYPE_MAPPING)
	{ "INVALID", InteractType_t::NUM_INTERACTOR_TYPE }
};

#define INTERACT_TYPE_TO_STRING_MAPPING(name) { InteractType_t:: name##_t, #name },

std::unordered_map<InteractType_t, std::string> InteractStringMap::s_interactTypeToString =
{
	ALL_TAG_MACRO(INTERACT_TYPE_TO_STRING_MAPPING)
	{ InteractType_t::NUM_INTERACTOR_TYPE, "INVALID" }
};

#undef INTERACT_STRING_TO_TYPE_MAPPING
#undef INTERACT_TYPE_TO_STRING_MAPPING
#include "entity/EntityMacroEnd.hpp"

void InteractStringMap::InteractPlayerCompHealingPadComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& healthComp = rReg.get<HealthComp>(rInteractorEntity);
	healthComp.m_health += 1;
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::CreateInteractionFnList()
{
	#define INSERT(interactor, interactable) fn[ \
		static_cast<int>(InteractType_t:: interactor##_t) * \
		static_cast<int>(InteractType_t::NUM_INTERACTOR_TYPE) + \
		static_cast<int>(InteractType_t:: interactable##_t)] \
			= InteractStringMap:: Interact ## interactor ## interactable;
	std::unordered_map<int, fnEntityInteractor> fn;
	INSERT(PlayerComp, HealingPadComp)
	#undef INSERT
	return fn;
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::fnInteractionMap
	= InteractStringMap::CreateInteractionFnList();