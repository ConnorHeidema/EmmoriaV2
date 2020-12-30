#ifndef __LIFESPAN_SYS__
#define __LIFESPAN_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

/**
 * This system handles interactions between 2 objects
 */
class LifespanSys
	: public System
{
public:
	LifespanSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	entt::registry& m_rReg;
};

#endif
