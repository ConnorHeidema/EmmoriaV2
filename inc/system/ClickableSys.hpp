#ifndef __CLICKABLE_SYS__
#define __CLICKABLE_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class ClickableSys
	: public ISystem
{
public:
	ClickableSys(entt::registry& rReg);
	void Update() override;
private:
	entt::registry& m_rReg;

	int m_xMousePosition;
	int m_yMousePosition;
	int m_MovieDelayFrame;
	int m_MovieDelayFrameMax;

	entt::entity m_entity;
};

#endif