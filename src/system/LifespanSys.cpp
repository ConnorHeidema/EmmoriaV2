#include "system/LifespanSys.hpp"

#include "component/functional/LifespanComp.hpp"

#include "component/InteractType.hpp"
#include "component/InteractStringMap.hpp"

#include "util/OverlapUtils.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include <iostream>

LifespanSys::LifespanSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void LifespanSys::Update_()
{
	m_rReg.view<LifespanComp>().each([&](auto entity, auto& lifespanComp)
	{
		if (!lifespanComp.m_framesToLive--) m_rReg.destroy(entity);
	});
}