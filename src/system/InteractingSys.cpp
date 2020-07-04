#include "system/InteractingSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"

#include "component/InteractType.hpp"

#include "util/OverlapUtils.hpp"

#include <iostream>

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
				if (interactableComp.m_interactType == InteractType_t::DialogChainComp_t &&
					interactorComp.m_interactType == InteractType_t::NUM_INTERACTOR_TYPE)
				{
					std::cout << "overlap detected between playercomp and healingpad comp" << std::endl;
				}
			}
		});
	});
}