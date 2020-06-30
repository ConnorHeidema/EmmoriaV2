#ifndef __HEALTH_SYS__
#define __HEALTH_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class HealthSys
	: public ISystem
{
public:
	HealthSys(entt::registry& reg);
	void Update() override;

private:
	entt::registry& m_rReg;
};

#endif