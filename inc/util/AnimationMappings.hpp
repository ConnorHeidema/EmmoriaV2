#ifndef __ANIMATION_MAPPINGS__
#define __ANIMATION_MAPPINGS__

#include "entt/entt.hpp"

#include <unordered_map>

using fnAnimationMapping = void(*)(entt::registry& rReg, entt::entity& rEntity, int& animation);

class AnimationMappings
{
public:
    static std::unordered_map<std::string, fnAnimationMapping> Create_map();
    static std::unordered_map<std::string, fnAnimationMapping> const m_animationMap;

	static void DawnPillarMapping(entt::registry& rReg, entt::entity& rEntity, int& animation);
};

#endif