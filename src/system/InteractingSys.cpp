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
	static_cast<int>(interactorComp.m_interactType) * \
	static_cast<int>(InteractType_t::NUM_INTERACTOR_TYPE) + \
	static_cast<int>(interactableComp.m_interactType)

InteractingSys::InteractingSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void InteractingSys::Update()
{
	m_rReg.view<PositionComp, SizeComp, InteractableComp>().each([&]
		(auto interactableEntity, auto& interactablePositionComp, auto& interactableSizeComp, auto& interactableComp)
	{
		m_rReg.view<PositionComp, SizeComp, InteractorComp>().each([&]
			(auto interactorEntity, auto& interactorPositionComp, auto& interactorSizeComp, auto& interactorComp)
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
		});
	});
}

#undef INDEX