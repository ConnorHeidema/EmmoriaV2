#include "system/SceneLoadSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/LoadComp.hpp"

#include <limits>
#include <iostream>

SceneLoadSys::SceneLoadSys(entt::registry& rReg)
	: m_rReg(rReg)
{
}

void SceneLoadSys::Update()
{
	bool bPlayerOnScreen = false;
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp)
	{
		bPlayerOnScreen = true;
	});
	if (bPlayerOnScreen)
	{
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp)
		{
			m_rReg.view<LocationComp>().each([&](auto locationEntity, auto& locationComp)
			{
				if (locationComp.xLocation != positionComp.m_position.x / ApplicationParameters::k_rightOfScreen ||
					locationComp.yLocation != positionComp.m_position.y / ApplicationParameters::k_bottomOfScreen)
				{

					locationComp.xLocation = positionComp.m_position.x / ApplicationParameters::k_rightOfScreen;
					locationComp.yLocation = positionComp.m_position.y / ApplicationParameters::k_bottomOfScreen;
					std::cout << "Changing location to: " << locationComp.area <<
						" (" << locationComp.xLocation << "," << locationComp.yLocation << ")" << std::endl;

					auto loadEntity = m_rReg.create();
					auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(loadEntity);
					fragmentLoadComp.m_filePath =
						locationComp.area + "/" +
						std::to_string(locationComp.xLocation) + "," +
						std::to_string(locationComp.yLocation);
				}
			});
		});
		return;
	}
	m_rReg.view<LocationComp>().each([&](auto locationEntity, auto& locationComp)
	{
		auto loadEntity = m_rReg.create();
		auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(loadEntity);
		fragmentLoadComp.m_filePath =
			locationComp.area + "/" +
			std::to_string(locationComp.xLocation) + "," +
			std::to_string(locationComp.yLocation);
	});
}