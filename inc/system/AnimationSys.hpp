#ifndef __ANIMATION_SYS__
#define __ANIMATION_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class AnimationSys
	: public System
{
public:
	AnimationSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	entt::registry& m_rReg;

	int m_currentAnimationCycle;

	static int const mk_animationSpeed;
};

#endif