#ifndef __ANIMATION_SYS__
#define __ANIMATION_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class AnimationSys
	: public ISystem
{
public:
	AnimationSys(entt::registry& rReg);
	void Update() override;
private:
	entt::registry& m_rReg;

	int m_currentAnimationCycle;

	static int const mk_animationSpeed;
};

#endif