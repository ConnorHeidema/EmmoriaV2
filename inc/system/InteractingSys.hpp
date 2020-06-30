#ifndef __INTERACTING_SYS__
#define __INTERACTING_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

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