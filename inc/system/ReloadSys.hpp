#ifndef __RELOAD_SYS__
#define __RELOAD_SYS__

#include "system/System.hpp"

#include "util/Latch.hpp"

#include <entt/entt.hpp>

class ReloadSys
	: public System
{
public:
	ReloadSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	void ReloadOnP_();
	void ReloadPerSecond_();

	void ReloadEverything_();

	entt::registry& m_rReg;
	Latch m_reloadLatch;
	static int const mk_restartFrame;
};

#endif