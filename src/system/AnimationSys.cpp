#include "system/AnimationSys.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/TileMapPieceComp.hpp"
#include "component/functional/TileMapComp.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include "util/AnimationMappings.hpp"
#include <entt/entt.hpp>
#include <iostream>

int const AnimationSys::mk_animationSpeed = 12;

AnimationSys::AnimationSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_animationProgressionlatch(mk_animationSpeed)
{ }

void AnimationSys::Update_()
{
	if (m_animationProgressionlatch.CheckLatch())
	{
		AnimateTileMapPieces_();
		AnimateSprites_();
	}
}

void AnimationSys::AnimateTileMapPieces_()
{
	std::string currentTileMap = "";
	m_rReg.view<TileMapComp>().each([&](
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

void AnimationSys::AnimateSprites_()
{
	#include "util/animation/AnimationMacro.hpp"
		#define SPRITE_ANIMATION_MAP(name) \
		m_rReg.view< name##Comp , SpriteComp>().each([&]( \
			auto entity, \
			auto& spriteComp) \
		{ \
			if (AnimationMappings::m_animationMap.find( #name ) != AnimationMappings::m_animationMap.end()) \
			{ \
				AnimationMappings::m_animationMap.at( #name )(m_rReg, entity, spriteComp.m_spriteIndex); \
			} else \
			{ \
				std::cout << \
					std::string("Could not find ") << \
					std::string( #name ) << \
					std::string(" animation mapping") << \
					std::endl; \
			} \
		});

		ALL_COMP_ANIMATION_MACRO(SPRITE_ANIMATION_MAP)
	#include "util/animation/AnimationMacroEnd.hpp"

}