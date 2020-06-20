#ifndef __PRINT_MOVEMENT_SYS__
#define __PRINT_MOVEMENT_SYS__

#include "system/ISystem.hpp"

class PrintMovementSys
	: public ISystem
{
public:
	void Update(entt::registry& reg) override;
};

#endif