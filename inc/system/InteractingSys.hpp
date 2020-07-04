#ifndef __INTERACTING_SYS__
#define __INTERACTING_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>


/**
 * This system handles interactions between 2 objects
 */
class InteractingSys
	: public ISystem
{
public:
	InteractingSys(entt::registry& rReg);
	void Update() override;
private:
	entt::registry& m_rReg;
};

#endif
