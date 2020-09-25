#include "system/SceneLoadSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/PositionComp.hpp"

#include <limits>
#include <iostream>

SceneLoadSys::SceneLoadSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_lastLocation { "", std::numeric_limits<int>::max(), std::numeric_limits<int>::max() }
{
		auto location = m_rReg.create();
		m_rReg.emplace<LocationComp>(location);
}

void SceneLoadSys::Update()
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
			}
		});
	});
}