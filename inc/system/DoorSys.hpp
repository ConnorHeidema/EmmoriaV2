#ifndef __DOOR_SYS__
#define __DOOR_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class DoorSys
	: public System
{
public:
	DoorSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif