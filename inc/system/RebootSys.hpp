#ifndef __REBOOT_SYS__
#define __REBOOT_SYS__

#include "system/System.hpp"

/**
 * Primary Components: RebootComp
 * Purpose:
 * 	The RebootSys will reboot everything whenever a RebootComponent
 *  has been created. For instance, on gameover, a reboot component
 *  will be created and consumed here.
 */
class RebootSys
	: public System
{
public:
	RebootSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
};

#endif