#include "system/InteractingSys.hpp"


#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"

#include "component/InteractType.hpp"
#include "component/InteractStringMap.hpp"

#include "util/OverlapUtils.hpp"
#include "util/EnttUtils.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include <SFML/Window.hpp>

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
	CreateNearbyPlayerEntity_();
	PerformObjectInteractions_();
	DestroyDeletedObjectsFromInteractions_();
}

void InteractingSys::CreateNearbyPlayerEntity_()
{
	m_rReg.view<PlayerComp, PositionComp, SizeComp>().each([&]
		(auto playerEntity, auto& playerPositionComp, auto& playerSizeComp)
	{
		if (EnttUtils<NearbyPlayerComp>::ComponentExists(m_rReg))
		{
			m_rReg.view<NearbyPlayerComp, PositionComp, SizeComp>().each([&]
				(auto nearbyPlayerEntity, auto& nearbyPlayerPositionComp, auto& nearbyPlayerSizeComp)
			{
				nearbyPlayerPositionComp.m_position.x = playerPositionComp.m_position.x /*- ApplicationParameters::k_widthAdjustment*/;
				nearbyPlayerPositionComp.m_position.y = playerPositionComp.m_position.y /*- ApplicationParameters::k_heightAdjustment*/;
				nearbyPlayerSizeComp.m_size.width = playerSizeComp.m_size.width + 2 * ApplicationParameters::k_widthAdjustment;
				nearbyPlayerSizeComp.m_size.height = playerSizeComp.m_size.height + 2 * ApplicationParameters::k_heightAdjustment;
			});
		}
		else
		{
			auto nearbyEntity = m_rReg.create();
			m_rReg.emplace<NearbyPlayerComp>(nearbyEntity);
			m_rReg.get_or_emplace<PositionComp>(nearbyEntity).m_position =
			{
				playerPositionComp.m_position.x /*- ApplicationParameters::k_widthAdjustment*/,
				playerPositionComp.m_position.y /*- ApplicationParameters::k_heightAdjustment*/
			};
			m_rReg.get_or_emplace<SizeComp>(nearbyEntity).m_size =
			{
				playerSizeComp.m_size.width + 2 * ApplicationParameters::k_widthAdjustment,
				playerSizeComp.m_size.height + 2 * ApplicationParameters::k_heightAdjustment
			};

			auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(nearbyEntity);
			interactorComp.m_interactTypeList.insert(InteractStringMap::s_interactStringToType.at("NearbyPlayerComp"));
		}
	});
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