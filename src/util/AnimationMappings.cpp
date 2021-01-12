#include "util/AnimationMappings.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include "component/functional/DoorComp.hpp"
#include "component/functional/SwitchComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/ChestComp.hpp"
#include "component/tag/AllTagComp.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "entt/entt.hpp"
#include <iostream>

std::unordered_map<std::string, fnAnimationMapping> AnimationMappings::Create_map()
{
	std::unordered_map<std::string, fnAnimationMapping> m;
#include "util/animation/AnimationMacro.hpp"
	#define ANIMATION_MAP(name) m[#name] = AnimationMappings::name##Mapping;
	ALL_ANIMATION_MACRO(ANIMATION_MAP)
#include "util/animation/AnimationMacroEnd.hpp"
	return m;
}

void AnimationMappings::DawnPillarMapping(entt::registry& /*rReg*/, entt::entity& /*rEntity*/, int& animation)
{
	switch (animation)
	{
		case DawnPillar::DAWN_PILLAR_GRASS_1: animation = DawnPillar::DAWN_PILLAR_GRASS_2; break;
		case DawnPillar::DAWN_PILLAR_GRASS_2: animation = DawnPillar::DAWN_PILLAR_GRASS_3; break;
		case DawnPillar::DAWN_PILLAR_GRASS_3: animation = DawnPillar::DAWN_PILLAR_GRASS_4; break;
		case DawnPillar::DAWN_PILLAR_GRASS_4: animation = DawnPillar::DAWN_PILLAR_GRASS_1; break;
		default: break;
	}
}

void AnimationMappings::BlobMapping(entt::registry& /*rReg*/, entt::entity& /*rEntity*/, int& animation)
{
	switch (animation)
	{
		case Blob::BLOB_1: animation = Blob::BLOB_2; break;
		case Blob::BLOB_2: animation = Blob::BLOB_3; break;
		case Blob::BLOB_3: animation = Blob::BLOB_4; break;
		case Blob::BLOB_4: animation = Blob::BLOB_1; break;
		default: break;
	}
}

void AnimationMappings::ChestTagMapping(entt::registry& rReg, entt::entity& rEntity, int& animation)
{
	animation = rReg.get<ChestComp>(rEntity).m_bOpened;
}

void AnimationMappings::PlayerMapping(entt::registry& rReg, entt::entity& /*rEntity*/, int& animation)
{
	rReg.view<PlayerComp, PositionComp>().each([&](auto& /*positionComp*/)
	{
		{
			using namespace sf;
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				switch (animation)
				{
					case Player::PLAYER_1: animation = Player::PLAYER_2; break;
					case Player::PLAYER_2: animation = Player::PLAYER_3; break;
					case Player::PLAYER_3: animation = Player::PLAYER_4; break;
					case Player::PLAYER_4: animation = Player::PLAYER_1; break;
					default: animation = Player::PLAYER_2; break;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::W))
			{
				switch (animation)
				{
					case Player::PLAYER_5: animation = Player::PLAYER_6; break;
					case Player::PLAYER_6: animation = Player::PLAYER_7; break;
					case Player::PLAYER_7: animation = Player::PLAYER_8; break;
					case Player::PLAYER_8: animation = Player::PLAYER_5; break;
					default: animation = Player::PLAYER_6; break;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				switch (animation)
				{
					case Player::PLAYER_9: animation = Player::PLAYER_10; break;
					case Player::PLAYER_10: animation = Player::PLAYER_11; break;
					case Player::PLAYER_11: animation = Player::PLAYER_12; break;
					case Player::PLAYER_12: animation = Player::PLAYER_9; break;
					default: animation = Player::PLAYER_10; break;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				switch (animation)
				{
					case Player::PLAYER_13: animation = Player::PLAYER_14; break;
					case Player::PLAYER_14: animation = Player::PLAYER_15; break;
					case Player::PLAYER_15: animation = Player::PLAYER_16; break;
					case Player::PLAYER_16: animation = Player::PLAYER_13; break;
					default: animation = Player::PLAYER_14; break;
				}
			}
			else
			{
				animation = 0;
			}
		}
	});
}

void AnimationMappings::DepressableMapping(entt::registry& rReg, entt::entity& rEntity, int& animation)
{
	auto& switchComp = rReg.get<SwitchComp>(rEntity);
	if (switchComp.m_bPressed && animation < 3)
	{
		animation++;
	}
	else if (!switchComp.m_bPressed && animation > 0)
	{
		animation--;
	}
}

void AnimationMappings::DoorLookingMapping(entt::registry& rReg, entt::entity& rEntity, int& animation)
{
	auto& doorComp = rReg.get<DoorComp>(rEntity);
	if (doorComp.m_bOpen && animation < 3)
	{
		animation++;
	}
	else if (!doorComp.m_bOpen && animation > 0)
	{
		animation--;
	}
}

std::unordered_map<std::string, fnAnimationMapping> const AnimationMappings::m_animationMap =  AnimationMappings::Create_map();
