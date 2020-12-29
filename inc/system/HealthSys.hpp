#ifndef __HEALTH_SYS__
#define __HEALTH_SYS__

#include "system/System.hpp"

class HealthSys
	: public System
{
public:
	HealthSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif