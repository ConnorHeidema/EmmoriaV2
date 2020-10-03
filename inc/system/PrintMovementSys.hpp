#ifndef __PRINT_MOVEMENT_SYS__
#define __PRINT_MOVEMENT_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class PrintMovementSys
	: public System
{
public:
	PrintMovementSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif