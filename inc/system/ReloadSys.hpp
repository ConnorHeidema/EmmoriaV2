#ifndef __RELOAD_SYS__
#define __RELOAD_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class ReloadSys
	: public System
{
public:
	ReloadSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
	int m_currentFrame;
	static int const mk_restartFrame;
};

#endif