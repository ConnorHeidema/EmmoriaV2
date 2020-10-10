#ifndef __SWITCH_SYS__
#define __SWITCH_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class SwitchSys
	: public System
{
public:
	SwitchSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif