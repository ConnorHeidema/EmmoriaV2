#ifndef __INTERACTING_SYS__
#define __INTERACTING_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>


/**
 * This system handles interactions between 2 objects
 */
class InteractingSys
	: public System
{
public:
	InteractingSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	entt::registry& m_rReg;
};

#endif
