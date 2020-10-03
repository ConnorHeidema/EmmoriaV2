#ifndef __PERSISTENT_SYS__
#define __PERSISTENT_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class PersistentSys
	: public System
{
public:
	PersistentSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;

	int m_framesToLive;
	int const m_kMaxFrameToLive;
	entt::registry& m_rReg;
};

#endif