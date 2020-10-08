#ifndef __MOVEMENT_SYS__
#define __MOVEMENT_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

/**
 * This system deals with the movement of all entities.
 * components utilised:
 *	 	PlayerComp
 * 		MovementComp
 */
class MovementSys
	: public System
{
public:
	MovementSys(std::string systemConfigItem, entt::registry& rReg);

private:
	void Update_() override;
	void UpdateLastPositions_();
	void UpdatePlayerPosition_();
	void UpdateArrowPosition_();

	entt::registry& m_rReg;

	float const& m_speed;
};

#endif