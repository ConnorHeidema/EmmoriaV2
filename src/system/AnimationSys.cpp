#include "system/AnimationSys.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/TileMapPieceComp.hpp"
#include "component/functional/TileMapComp.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include "util/AnimationMappings.hpp"

#include <string.h>

int const AnimationSys::mk_animationSpeed = 12;

AnimationSys::AnimationSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_currentAnimationCycle(0)
{ }

void AnimationSys::Update()
{
	if (m_currentAnimationCycle != mk_animationSpeed)
	{
		m_currentAnimationCycle++;
		return;
	}

	{
		std::string currentTileMap = "";
		m_rReg.view<TileMapComp>().each([&](
			auto entity,
			auto& tileMapComp)
		{
			currentTileMap = tileMapComp.m_tileMapBase;
		});

		m_rReg.view<TileMapPieceComp>().each([&](
			auto entity,
			auto& tileMapPieceComp)
		{
			if (AnimationMappings::m_animationMap.find(currentTileMap) != AnimationMappings::m_animationMap.end())
			{
				AnimationMappings::m_animationMap.at(currentTileMap)(m_rReg, entity, tileMapPieceComp.m_index);
			}
		});
	}

	m_rReg.view<BlobComp, SpriteComp>().each([&](
		auto entity,
		auto& spriteComp)
	{
		if (AnimationMappings::m_animationMap.find("Blob") != AnimationMappings::m_animationMap.end())
		{
			AnimationMappings::m_animationMap.at("Blob")(m_rReg, entity, spriteComp.m_spriteIndex);
		}
	});

	m_rReg.view<PlayerComp, SpriteComp>().each([&](
		auto entity,
		auto& spriteComp)
	{
		if (AnimationMappings::m_animationMap.find("Player") != AnimationMappings::m_animationMap.end())
		{
			AnimationMappings::m_animationMap.at("Player")(m_rReg, entity, spriteComp.m_spriteIndex);
		}
	});

	m_currentAnimationCycle = 0;
}