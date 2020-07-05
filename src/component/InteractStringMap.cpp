#include "component/InteractStringMap.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/functional/HealthComp.hpp"
#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"

#include "util/OverlapUtils.hpp"

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

void InteractStringMap::InteractPlayerCompWallComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& wallPositionComp = rReg.get<PositionComp>(rInteractableEntity);
	auto& wallSizeComp = rReg.get<SizeComp>(rInteractableEntity);

	auto& playerLastPositionComp = rReg.get<LastPositionComp>(rInteractorEntity);
	auto& playerPositionComp = rReg.get<PositionComp>(rInteractorEntity);
	auto& playerSizeComp = rReg.get<SizeComp>(rInteractorEntity);

	Position lastPlayerXposition = {playerLastPositionComp.m_lastPosition.x, playerPositionComp.m_position.y};
	Position lastPlayerYposition = {playerPositionComp.m_position.x, playerLastPositionComp.m_lastPosition.y};


	if (OverlapUtils::Overlapping(
		wallPositionComp.m_position,
		wallSizeComp.m_size,
		lastPlayerXposition,
		playerSizeComp.m_size))
	{
		playerPositionComp.m_position.y = playerLastPositionComp.m_lastPosition.y;
	}
	if (OverlapUtils::Overlapping(
		wallPositionComp.m_position,
		wallSizeComp.m_size,
		lastPlayerYposition,
		playerSizeComp.m_size))
	{
		playerPositionComp.m_position.x = playerLastPositionComp.m_lastPosition.x;
	}
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
	INSERT(PlayerComp, WallComp)
	#undef INSERT
	return fn;
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::fnInteractionMap
	= InteractStringMap::CreateInteractionFnList();