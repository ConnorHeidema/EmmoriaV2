#ifndef __ANIMATION_SYS__
#define __ANIMATION_SYS__

#include "system/System.hpp"

#include "util/Latch.hpp"

#include <entt/entt.hpp>

class AnimationSys
	: public System
{
public:
	AnimationSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;
	void AnimateTileMapPieces_();
	void AnimateSprites_();

	entt::registry& m_rReg;

	Latch m_latch;

	static int const mk_animationSpeed;
};

#endif