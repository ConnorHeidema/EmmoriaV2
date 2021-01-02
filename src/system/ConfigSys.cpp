#include "system/ConfigSys.hpp"

#include "config/ConfigItems.hpp"
#include "util/SystemList.hpp"

int const ConfigSys::updateRate = 60;
std::string const ConfigSys::k_configFileName = "data/Config/config.ini";

ConfigSys::ConfigSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_configUpdateLatch(updateRate)
{
	ConfigItems::LoadConfigFile(k_configFileName);
}
#include "system/SystemMacro.hpp"
#define SET_RUNNING(sys) \
	SystemList::m_pSystemList[static_cast<int>(SystemId_t:: sys ## _t)]->SetRunning(\
		configItems.find(std::string("Disable") + std::string(#sys) + std::string("Sys")) == configItems.end());

void ConfigSys::Update_()
{
	if (m_configUpdateLatch.CheckLatch())
	{
		ConfigItems::LoadConfigFile(k_configFileName);
		auto& configItems = ConfigItems::m_setConfigItems;
		DO_MACRO_FOR_ALL_SYSTEMS(SET_RUNNING, SET_RUNNING);
	}
}
#include "system/SystemMacroEnd.hpp"