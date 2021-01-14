#ifndef __LIGHT_SYS__
#define __LIGHT_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

class LightSys
	: public System {
public:
	LightSys(std::string systemConfigItem, entt::registry& reg);
private:
	void Update_() override;

	entt::registry& m_rReg;
};

#endif