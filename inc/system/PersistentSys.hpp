#ifndef __PERSISTENT_SYS__
#define __PERSISTENT_SYS__

#include "system/System.hpp"

#include "util/Latch.hpp"

#include <entt/entt.hpp>

class PersistentSys
	: public System
{
public:
	PersistentSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;

	entt::registry& m_rReg;
	Latch m_frameToLiveLatch;

	static int const mk_MaxFramesToLive;
};

#endif