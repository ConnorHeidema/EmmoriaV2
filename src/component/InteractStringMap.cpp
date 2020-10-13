#include "component/InteractStringMap.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/LocationComp.hpp"
#include "component/functional/SwitchComp.hpp"
#include "component/functional/DoorComp.hpp"
#include "component/functional/stats/MaxHealthComp.hpp"

#include "util/OverlapUtils.hpp"
#include "util/PositionUtils.hpp"

#include <iostream>
#include <limits>

#include <SFML/Window.hpp>

#include "entity/EntityMacro.hpp"
#define INTERACT_STRING_TO_TYPE_MAPPING(name) { #name , InteractType_t:: name##_t },
std::unordered_map<std::string, InteractType_t> InteractStringMap::s_interactStringToType =
{
	ALL_TAG_MACRO(INTERACT_STRING_TO_TYPE_MAPPING)
	{ "INVALID", InteractType_t::NUM_INTERACTOR_TYPE }
};
#undef INTERACT_STRING_TO_TYPE_MAPPING

#define INTERACT_TYPE_TO_STRING_MAPPING(name) { InteractType_t:: name##_t, #name },
std::unordered_map<InteractType_t, std::string> InteractStringMap::s_interactTypeToString =
{
	ALL_TAG_MACRO(INTERACT_TYPE_TO_STRING_MAPPING)
	{ InteractType_t::NUM_INTERACTOR_TYPE, "INVALID" }
};
#undef INTERACT_TYPE_TO_STRING_MAPPING
#include "entity/EntityMacroEnd.hpp"

void InteractStringMap::InteractPlayerCompHealingPadComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& healthComp = rReg.get<HealthComp>(rInteractorEntity);
	int maxHealth = INT32_MAX;
	if (rReg.has<MaxHealthComp>(rInteractorEntity))
	{
		maxHealth = rReg.get<MaxHealthComp>(rInteractorEntity).m_maxHealth;
	}
	healthComp.m_health = std::min(healthComp.m_health + 1, maxHealth);
}

void InteractStringMap::InteractPlayerCompBlobComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& healthComp = rReg.get<HealthComp>(rInteractorEntity);
	healthComp.m_health -= 1;
}

void InteractStringMap::InteractWallInteractorCompWallComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& playerPosition = rReg.get<PositionComp>(rInteractorEntity).m_position;
	auto& playerLastPosition = rReg.get<LastPositionComp>(rInteractorEntity).m_lastPosition;
	auto& playerSize = rReg.get<SizeComp>(rInteractorEntity).m_size;
	auto& wallPosition = rReg.get<PositionComp>(rInteractableEntity).m_position;
	auto& wallSize = rReg.get<SizeComp>(rInteractableEntity).m_size;
	PositionUtils::SetObjectToViablePosition(playerPosition, playerLastPosition, playerSize, wallPosition, wallSize);
}

void InteractStringMap::InteractArrowCompBlobComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	rReg.emplace_or_replace<DeleteAfterInteractionComp>(rInteractorEntity);
	auto& blobHealth = rReg.get_or_emplace<HealthComp>(rInteractableEntity).m_health;
	blobHealth -= 5;
}

void InteractStringMap::InteractPlayerCompHoleComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		rReg.view<PlayerComp, PositionComp, HealthComp>().each([&](auto entity, auto& positionComp, auto& healthComp)
		{
			healthComp.m_health /= 2;
			healthComp.m_health -= 1;
			positionComp.m_position.x = locationComp.xSpawnLocation;
			positionComp.m_position.y = locationComp.ySpawnLocation;
		});
	});
}

void InteractStringMap::InteractBlobCompHoleComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& blobLastPosition = rReg.get<LastPositionComp>(rInteractorEntity).m_lastPosition;
	auto& blobPosition = rReg.get<PositionComp>(rInteractorEntity).m_position;
	auto& blobSize = rReg.get<SizeComp>(rInteractorEntity).m_size;

	auto& wallPosition = rReg.get<PositionComp>(rInteractableEntity).m_position;
	auto& wallSize = rReg.get<SizeComp>(rInteractableEntity).m_size;
	PositionUtils::SetObjectToViablePosition(blobPosition, blobLastPosition, blobSize, wallPosition, wallSize);
}

void InteractStringMap::InteractDepressableCompWeightComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& switchComp = rReg.get_or_emplace<SwitchComp>(rInteractorEntity);
	switchComp.m_bPressed = true;
	rReg.view<DoorComp>().each([&](auto entity, auto& doorComp)
	{
		if (switchComp.m_action == doorComp.m_action)
		{
			doorComp.m_bOpen = true;
		}
	});
}

void InteractStringMap::InteractNearbyPlayerCompSignComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		std::cout << "Space pressed on sign" << std::endl;
	}
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::CreateInteractionFnList()
{
#include "component/InteractMacro.hpp"
	#define INSERT(interactor, interactable) fn[ \
		static_cast<int>(InteractType_t:: interactor##Comp_t) * \
		static_cast<int>(InteractType_t::NUM_INTERACTOR_TYPE) + \
		static_cast<int>(InteractType_t:: interactable##Comp_t)] \
			= InteractStringMap:: Interact ## interactor ## Comp ## interactable ## Comp;
	std::unordered_map<int, fnEntityInteractor> fn;
	ALL_INTERACTIONS(INSERT)
#include "component/EndInteractMacro.hpp"
	#undef INSERT
	return fn;
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::fnInteractionMap
	= InteractStringMap::CreateInteractionFnList();