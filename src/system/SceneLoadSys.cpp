#include "system/SceneLoadSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/LocationComp.hpp"

#include <entt/entt.hpp>

#include <cmath>
#include <limits>
#include <iostream>

SceneLoadSys::SceneLoadSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{
}

void SceneLoadSys::Update_()
{
	bool bPlayerOnScreen = false;
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto& /*positionComp*/)
	{
		bPlayerOnScreen = true;
	});
	if (bPlayerOnScreen)
	{
		CreateLoadCompFromLocationCompWithPlayer_();
		return;
	}
	CreateLoadCompFromLocationComp_();
}

void SceneLoadSys::CreateLoadCompFromLocationComp_()
{
	m_rReg.view<LocationComp>().each([&](auto& locationComp)
	{
		m_rReg.clear<DeloadableComp>();
		auto loadEntity = m_rReg.create();
		auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(loadEntity);
		fragmentLoadComp.m_filePath =
			locationComp.area + "/" +
			std::to_string(int(locationComp.xLocation)) + "," +
			std::to_string(int(locationComp.yLocation));
	});
}

void SceneLoadSys::CreateLoadCompFromLocationCompWithPlayer_()
{
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto& positionComp)
	{
		m_rReg.view<LocationComp>().each([&](auto& locationComp)
		{
			if (locationComp.xLocation != (int)floor((double)positionComp.m_position.x / ApplicationParameters::k_rightOfScreen) ||
				locationComp.yLocation != (int)floor((double)positionComp.m_position.y / ApplicationParameters::k_bottomOfScreen) ||
				locationComp.area != m_lastArea ||
				!locationComp.m_bLoaded ||
				(locationComp.xLocation == 0 && positionComp.m_position.x < 0) ||
				(locationComp.yLocation == 0 && positionComp.m_position.y < 0))
			{
				locationComp.m_bLoaded = true;
				locationComp.xLocation = (int)floor((double)positionComp.m_position.x / ApplicationParameters::k_rightOfScreen);
				locationComp.yLocation = (int)floor((double)positionComp.m_position.y / ApplicationParameters::k_bottomOfScreen);
				locationComp.xSpawnLocation = (int)positionComp.m_position.x;
				locationComp.ySpawnLocation = (int)positionComp.m_position.y;

				std::cout << "Changing location to: " << locationComp.area <<
					" (" << locationComp.xLocation << "," << locationComp.yLocation << ")" << std::endl;

				m_rReg.view<DeloadableComp>().each([&](auto deloadableEntity)
				{
					m_rReg.destroy(deloadableEntity);
				});
				auto loadEntity = m_rReg.create();
				auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(loadEntity);
				fragmentLoadComp.m_filePath =
					locationComp.area + "/" +
					std::to_string(int(locationComp.xLocation)) + "," +
					std::to_string(int(locationComp.yLocation));
			}
			m_lastArea = locationComp.area;
		});
	});
}