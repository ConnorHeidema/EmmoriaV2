#include "system/ReloadSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "config/ConfigItems.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/LocationComp.hpp"

#include <entt/entt.hpp>
#include <SFML/Window/Keyboard.hpp>

int const ReloadSys::mk_restartFrame = 60;


ReloadSys::ReloadSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_reloadLatch(mk_restartFrame)
{}

void ReloadSys::Update_()
{
	ReloadOnP_();
	ReloadPerSecond_();
}

void ReloadSys::ReloadOnP_()
{
	if (ConfigItems::m_setConfigItems.find("ReloadOnP") == ConfigItems::m_setConfigItems.end() ||
		!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		return;
	}
	ReloadEverything_();
}

void ReloadSys::ReloadPerSecond_()
{
	if (ConfigItems::m_setConfigItems.find("ReloadPerSecond") == ConfigItems::m_setConfigItems.end() ||
		!m_reloadLatch.CheckLatch())
	{
		return;
	}
	ReloadEverything_();
}

void ReloadSys::ReloadEverything_()
{
	m_rReg.view<DeloadableComp>().each([&](auto entity)
	{
		m_rReg.destroy(entity);
	});
	m_rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		auto loadEntity = m_rReg.create();
		auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(loadEntity);
		fragmentLoadComp.m_filePath =
			locationComp.area + "/" +
			std::to_string(int(locationComp.xLocation)) + "," +
			std::to_string(int(locationComp.yLocation));
	});
}