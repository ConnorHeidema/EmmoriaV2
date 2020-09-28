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

#include "util/animation/AnimationMacro.hpp"
#define DEFINE_ANIMATION_MAPPINGS(name) static void name##Mapping(entt::registry& rReg, entt::entity& rEntity, int& animation);
	ALL_ANIMATION_MACRO(DEFINE_ANIMATION_MAPPINGS)
#include "util/animation/AnimationMacroEnd.hpp"
};

#endif