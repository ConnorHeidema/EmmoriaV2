#ifndef __MOVEMENT_SYS__
#define __MOVEMENT_SYS__

#include "system/ISystem.hpp"

/**
 * This system deals with the movement of all entities.
 * components utilised:
 *	 	PlayerComp
 * 		MovementComp
 */
class MovementSys
	: public ISystem
{
public:
	void Update(entt::registry& reg) override;
};

#endif