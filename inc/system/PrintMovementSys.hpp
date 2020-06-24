#ifndef __PRINT_MOVEMENT_SYS__
#define __PRINT_MOVEMENT_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class PrintMovementSys
	: public ISystem
{
public:
	PrintMovementSys(entt::registry& reg);
	void Update() override;

private:
	entt::registry& m_rReg;
};

#endif