#include "system/InteractingSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"

#include "component/InteractType.hpp"
#include "component/InteractStringMap.hpp"

#include "util/OverlapUtils.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include <iostream>

#define INDEX() \
	static_cast<int>(interactorType) * \
	static_cast<int>(InteractType_t::NUM_INTERACTOR_TYPE) + \
	static_cast<int>(interactableType)

InteractingSys::InteractingSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

// Have to deal with segfault where interact entities are destroyed in map but we are trying to iterate over them still
void InteractingSys::Update_()
{
	PerformObjectInteractions_();
	DestroyDeletedObjectsFromInteractions_();

}

void InteractingSys::PerformObjectInteractions_()
{
	m_rReg.view<PositionComp, SizeComp, InteractableComp>().each([&]
		(auto interactableEntity, auto& interactablePositionComp, auto& interactableSizeComp, auto& interactableComp)
	{
		m_rReg.view<PositionComp, SizeComp, InteractorComp>().each([&]
			(auto interactorEntity, auto& interactorPositionComp, auto& interactorSizeComp, auto& interactorComp)
		{
			for (auto& interactableType : interactableComp.m_interactTypeList)
			{
				for (auto& interactorType : interactorComp.m_interactTypeList)
				{
					if (OverlapUtils::Overlapping(
						interactablePositionComp.m_position,
						interactableSizeComp.m_size,
						interactorPositionComp.m_position,
						interactorSizeComp.m_size))
					{
						if (InteractStringMap::fnInteractionMap.find(INDEX()) !=
							InteractStringMap::fnInteractionMap.end())
						{
							InteractStringMap::fnInteractionMap.at(INDEX())(
								m_rReg,
								interactorEntity,
								interactableEntity);
						}
					}
				}
			}
		});
	});
}

void InteractingSys::DestroyDeletedObjectsFromInteractions_()
{
	m_rReg.view<DeleteAfterInteractionComp>().each([&](auto deleteAfterInteractionEntity)
	{
		m_rReg.destroy(deleteAfterInteractionEntity);
	});
}

#undef INDEX