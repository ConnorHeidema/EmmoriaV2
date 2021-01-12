#include "system/PersistentSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/PositionComp.hpp"

#include <entt/entt.hpp>

int const PersistentSys::mk_MaxFramesToLive = 24;

PersistentSys::PersistentSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_frameToLiveLatch(mk_MaxFramesToLive)
{ }

void PersistentSys::Update_()
{
	bool m_bPersistentCompExists = false;
	m_rReg.view<PersistentComp>().each([&]()
	{
		m_bPersistentCompExists = true;
	});
	if (m_bPersistentCompExists)
	{
		if (m_frameToLiveLatch.CheckLatch())
		{
			m_rReg.view<PositionComp>(entt::exclude<PersistentComp>).each([&](auto entity, auto& /*posComp*/)
			{
				m_rReg.destroy(entity);
			});
			// Should find any other entities that need destroying as well...
			// May need to work with other components in the future
		}
	}
}