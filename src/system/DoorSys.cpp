#include "system/DoorSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/InteractStringMap.hpp"

#include "component/functional/DoorComp.hpp"
#include "component/functional/InteractableComp.hpp"

DoorSys::DoorSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void DoorSys::Update_()
{
	m_rReg.view<DoorComp>().each([&](auto entity, auto& doorComp)
	{
		if (doorComp.m_bOpen)
		{
			m_rReg.remove_if_exists<WallComp>(entity);
			auto& interactableComp = m_rReg.get_or_emplace<InteractableComp>(entity);
			interactableComp.m_interactTypeList.erase(InteractStringMap::s_interactStringToType.at("WallComp"));
		}
		else
		{
			m_rReg.emplace_or_replace<WallComp>(entity);
			auto& interactableComp = m_rReg.get_or_emplace<InteractableComp>(entity);
			if (interactableComp.m_interactTypeList
				.find(InteractStringMap::s_interactStringToType.at("WallComp")) == interactableComp.m_interactTypeList.end())
				interactableComp.m_interactTypeList.insert(InteractStringMap::s_interactStringToType.at("WallComp"));
		}
	});
}
