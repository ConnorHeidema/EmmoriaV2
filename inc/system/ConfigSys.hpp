#ifndef __CONFIG_SYS__
#define __CONFIG_SYS__

#include "system/System.hpp"

#include "util/Latch.hpp"

#include <entt/entt.hpp>

#include <SFML/Window.hpp>

class ConfigSys
	: public System
{
public:
	ConfigSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	Latch m_configUpdateLatch;
	entt::registry& m_rReg;
	static int const updateRate;
};

#endif