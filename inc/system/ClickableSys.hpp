#ifndef __CLICKABLE_SYS__
#define __CLICKABLE_SYS__

#include "system/ISystem.hpp"

class ClickableSys
	: public ISystem
{
public:
	ClickableSys();

	void Update(entt::registry& reg) override;
private:
	bool IsCollisionDetected_(int const& left, int const& top, int const& width, int const& height);

	int m_xMousePosition;
	int m_yMousePosition;
	int m_MovieDelayFrame;
	int m_MovieDelayFrameMax;

	entt::entity m_entity;
};

#endif