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
	MovementSys();
	void Update(entt::registry& reg) override;

private:
	int const& m_speed;
};

#endif