#include "system/PersistentSys.hpp"

#include "component/tag/PersistentComp.hpp"

#include "component/functional/PositionComp.hpp"

PersistentSys::PersistentSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_framesToLive(0)
	, m_kMaxFrameToLive(24)
{ }

void PersistentSys::Update()
{
	bool m_bPersistentCompExists = false;
	m_rReg.view<PersistentComp>().each([&](auto entity)
	{
		m_bPersistentCompExists = true;
	});
	if (m_bPersistentCompExists)
	{
		m_framesToLive++;
	}
	if (m_framesToLive == m_kMaxFrameToLive)
	{
		m_rReg.view<PositionComp>(entt::exclude<PersistentComp>).each([&](auto entity, auto& posComp)
		{
			m_rReg.destroy(entity);
		});
		// Should find any other entities that need destroying as well...
		// May need to work with other components in the future
	}
}