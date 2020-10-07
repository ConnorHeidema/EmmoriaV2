#ifndef __REBOOT_SYS__
#define __REBOOT_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class RebootSys
	: public System
{
public:
	RebootSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif