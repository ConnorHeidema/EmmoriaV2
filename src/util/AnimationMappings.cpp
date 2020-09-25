#include "util/AnimationMappings.hpp"

#include "TileMap/TileMapIndexes.hpp"


std::unordered_map<std::string, fnAnimationMapping> AnimationMappings::Create_map()
{
	std::unordered_map<std::string, fnAnimationMapping> m;
	#define ANIMATION_MAP(name) m[#name] = AnimationMappings:: name##Mapping;
	ANIMATION_MAP(DawnPillar)
	return m;
}

void AnimationMappings::DawnPillarMapping(entt::registry& rReg, entt::entity& rEntity, int& animation)
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


std::unordered_map<std::string, fnAnimationMapping> const AnimationMappings::m_animationMap =  AnimationMappings::Create_map();
