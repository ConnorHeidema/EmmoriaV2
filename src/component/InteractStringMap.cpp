#include "component/InteractStringMap.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/LocationComp.hpp"

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

void InteractStringMap::InteractPlayerCompBlobComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& healthComp = rReg.get<HealthComp>(rInteractorEntity);
	healthComp.m_health -= 1;
}

void InteractStringMap::InteractWallInteractorCompWallComp(entt::registry& rReg, entt::entity& rInteractorEntity, entt::entity& rInteractableEntity)
{
	auto& wallPosition = rReg.get<PositionComp>(rInteractableEntity).m_position;
	auto& wallSize = rReg.get<SizeComp>(rInteractableEntity).m_size;

	auto& playerLastPosition = rReg.get<LastPositionComp>(rInteractorEntity).m_lastPosition;
	auto& playerPosition = rReg.get<PositionComp>(rInteractorEntity).m_position;
	auto& playerSize = rReg.get<SizeComp>(rInteractorEntity).m_size;

	Position lastPlayerXposition = {playerLastPosition.x, playerPosition.y};
	Position lastPlayerYposition = {playerPosition.x, playerLastPosition.y};

	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastPlayerYposition, playerSize))
	{
		playerPosition.x = playerLastPosition.x;
	}
	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastPlayerXposition, playerSize))
	{
		playerPosition.y = playerLastPosition.y;
	}
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
	auto& wallPosition = rReg.get<PositionComp>(rInteractableEntity).m_position;
	auto& wallSize = rReg.get<SizeComp>(rInteractableEntity).m_size;

	auto& blobLastPosition = rReg.get<LastPositionComp>(rInteractorEntity).m_lastPosition;
	auto& blobPosition = rReg.get<PositionComp>(rInteractorEntity).m_position;
	auto& blobSize = rReg.get<SizeComp>(rInteractorEntity).m_size;

	Position lastBlobXposition = {blobLastPosition.x, blobPosition.y};
	Position lastBlobYposition = {blobPosition.x, blobLastPosition.y};

	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastBlobYposition, blobSize))
	{
		blobPosition.x = blobLastPosition.x;
	}
	if (OverlapUtils::Overlapping(wallPosition, wallSize, lastBlobXposition, blobSize))
	{
		blobPosition.y = blobLastPosition.y;
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
	INSERT(PlayerComp, BlobComp)
	INSERT(WallInteractorComp, WallComp)
	INSERT(ArrowComp, BlobComp)
	INSERT(PlayerComp, HoleComp)
	INSERT(BlobComp, HoleComp)
	#undef INSERT
	return fn;
}

std::unordered_map<int, fnEntityInteractor> InteractStringMap::fnInteractionMap
	= InteractStringMap::CreateInteractionFnList();