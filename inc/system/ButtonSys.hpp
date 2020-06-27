#ifndef __BUTTON_SYS__
#define __BUTTON_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class ButtonSys
	: public ISystem
{
public:
	ButtonSys(entt::registry& rReg);
	void Update() override;
private:
	entt::registry& m_rReg;

	int m_MovieDelayFrame;
	int m_MovieDelayFrameMax;

	entt::entity m_entity;
};

#endif