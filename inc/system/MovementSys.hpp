#ifndef __MOVEMENT_SYS__
#define __MOVEMENT_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

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
	MovementSys(entt::registry& rReg);
	void Update() override;

private:
	entt::registry& m_rReg;

	int const& m_speed;
};

#endif