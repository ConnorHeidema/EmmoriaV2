#include "system/InteractingSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"
#include "component/functional/RotationComp.hpp"

#include "component/InteractType.hpp"
#include "component/InteractStringMap.hpp"

#include "util/OverlapUtils.hpp"
#include "util/EnttUtils.hpp"
#include "util/datastructure/QuadTree.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include <ltbl/lighting/LightShape.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <util/Graphics/RectangularBoundaryCollision.hpp>
#include <iostream>
#include <list>

#include <math.h>

#define INDEX() \
	static_cast<int>(interactorType) * \
	static_cast<int>(InteractType_t::NUM_INTERACTOR_TYPE) + \
	static_cast<int>(interactableType)

InteractingSys::InteractingSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{
	// to be removed when light works on ubuntu
	ltbl::LightShape light;
}

// Have to deal with segfault where interact entities are destroyed in map but we are trying to iterate over them still
void InteractingSys::Update_()
{
	CreateNearbyPlayerEntity_();
	PerformObjectInteractions_();
	DestroyDeletedObjectsFromInteractions_();
}

void InteractingSys::CreateNearbyPlayerEntity_()
{
	m_rReg.view<PlayerComp, PositionComp, SizeComp>().each([&](
		auto& playerPositionComp, 
		auto& playerSizeComp)
	{
		if (EnttUtils<NearbyPlayerComp>::ComponentExists(m_rReg))
		{
			m_rReg.view<NearbyPlayerComp, PositionComp, SizeComp>().each([&](
				auto& nearbyPlayerPositionComp, 
				auto& nearbyPlayerSizeComp)
			{
				nearbyPlayerPositionComp.m_position.x = playerPositionComp.m_position.x;
				nearbyPlayerPositionComp.m_position.y = playerPositionComp.m_position.y;
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
				playerPositionComp.m_position.x,
				playerPositionComp.m_position.y
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
	auto const k_tan1 = tanf(1);
	sf::RectangleShape interactableObject;
	sf::RectangleShape interactorObject;
	/* Quadtree should be implemented over contiguous memory... @todo connor */
	//std::list<entt::entity> interactorList;
	//QuadTree interactableQuadMap(0, 0, ApplicationParameters::k_rightOfScreen, ApplicationParameters::k_bottomOfScreen);
	m_rReg.view<PositionComp, SizeComp, InteractableComp>().each([&]
		(auto interactableEntity, auto& interactablePositionComp, auto& interactableSizeComp, auto& interactableComp)
	{
		m_rReg.view<PositionComp, SizeComp, InteractorComp>().each([&]
			(auto interactorEntity, auto& interactorPositionComp, auto& interactorSizeComp, auto& interactorComp)
		{
			// Need to insert everything into quadmap and do it that way instead...
			if (interactableEntity == interactorEntity)
				return;

			for (auto& interactableType : interactableComp.m_interactTypeList)
			{
				for (auto& interactorType : interactorComp.m_interactTypeList)
				{
					bool bPerformInteraction = false;
					auto& posable = interactablePositionComp.m_position;
					auto& sizeable = interactableSizeComp.m_size;
					auto& posor = interactorPositionComp.m_position;
					auto& sizeor = interactorSizeComp.m_size;
					if (!m_rReg.has<RotationComp>(interactableEntity) &&
						!m_rReg.has<RotationComp>(interactorEntity))
					{
						if (OverlapUtils::Overlapping(posable, sizeable, posor, sizeor))
							bPerformInteraction = true;
					}
					else
					{
						{
							interactableObject.setPosition(sf::Vector2f((float)posable.x, (float)posable.y));
							interactableObject.setSize(sf::Vector2f((float)sizeable.width, (float)sizeable.height));
							interactableObject.setOrigin(sizeable.width / 2.f, sizeable.height / 2.f);
							if (m_rReg.has<RotationComp>(interactableEntity)) {
								auto& angle = m_rReg.get<RotationComp>(interactableEntity).m_angle;
								interactableObject.setRotation(float((angle * 90.L / k_tan1) + 90.L));
							}
							else 								
							{
								interactableObject.setRotation(0);
							}
						}

						{
							interactorObject.setPosition(sf::Vector2f((float)posor.x, (float)posor.y));
							interactorObject.setSize(sf::Vector2f((float)sizeor.width, (float)sizeor.height));
							interactorObject.setOrigin((float)sizeor.width / 2.f, (float)sizeor.height / 2.f);
							if (m_rReg.has<RotationComp>(interactorEntity)) {
								auto& angle = m_rReg.get<RotationComp>(interactorEntity).m_angle;
								interactorObject.setRotation(float((angle * 90.L / k_tan1) + 90.L));
							} 
							else 
							{
								interactorObject.setRotation(0);
							}
						}
						bPerformInteraction = collision::areColliding(interactableObject, interactorObject);
					}
					


					if (bPerformInteraction)
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