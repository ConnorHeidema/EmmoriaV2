#include "system/ConfigSys.hpp"

#include "config/ConfigItems.hpp"

ConfigSys::ConfigSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, currentFrame(0)
{ }

void ConfigSys::Update_()
{
	if (currentFrame != updateRate)
	{
		currentFrame++;
		return;
	}
	currentFrame = 0;
	ConfigItems::m_setConfigItems.clear();
	ConfigItems::LoadConfigFile("data/Config/config.ini");
}

int const ConfigSys::updateRate = 60;