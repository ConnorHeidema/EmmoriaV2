#ifndef __PERSISTENT_SYS__
#define __PERSISTENT_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class PersistentSys
	: public ISystem
{
public:
	PersistentSys(entt::registry& reg);
	void Update() override;

private:
	int m_framesToLive;
	int const m_kMaxFrameToLive;
	entt::registry& m_rReg;
};

#endif