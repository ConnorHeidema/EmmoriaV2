#include "system/BowSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/InteractorComp.hpp"

#include "component/InteractType.hpp"

#include "util/Mediamap.hpp"

#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>

const int BowSys::mk_frequency = 30;
const int BowSys::mk_arrowWidthUnits = 2;
const int BowSys::mk_arrowHeightUnits = 5;

BowSys::BowSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_bowFrequencyLatch(mk_frequency)
{ }

void BowSys::Update_()
{
	if (m_bowFrequencyLatch.Peek())
	{
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& playerPositionComp)
		{
			bool bPerformAction = false;
			m_rReg.view<ItemActionAreaComp, ClickableComp>().each([&](auto entity, auto& clickableActionArea)
			{
				if (clickableActionArea.m_bLeftClicked)
				{
					CreateArrow_(playerPositionComp, clickableActionArea);
					m_bowFrequencyLatch.Reset();
				}
			});
		});
	}
	else
	{
		m_bowFrequencyLatch.CheckLatch();
	}
}

void BowSys::CreateArrow_(
	PositionComp& playerPositionComp,
	ClickableComp& clickableActionArea)
{
	auto bowArrowEntity = m_rReg.create();
	auto& bowArrowPositionComp = m_rReg.emplace<PositionComp>(bowArrowEntity);
	bowArrowPositionComp.m_position.x = playerPositionComp.m_position.x;
	bowArrowPositionComp.m_position.y = playerPositionComp.m_position.y;
	auto& renderable = m_rReg.emplace<RenderableComp>(bowArrowEntity);
	renderable.m_bRendered = false;
	auto& spriteComp = m_rReg.emplace<SpriteComp>(bowArrowEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + "Arrow" + ApplicationParameters::k_pictureExt;
	m_rReg.emplace<ArrowComp>(bowArrowEntity);


	m_rReg.emplace_or_replace<DeloadableComp>(bowArrowEntity);

	auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(bowArrowEntity);
	interactorComp.m_interactTypeList.emplace_back(InteractType_t::ArrowComp_t);

	auto& rotationComp = m_rReg.emplace<RotationComp>(bowArrowEntity);

	double adjustedPlayerPositionX = playerPositionComp.m_position.x /
		ApplicationParameters::k_widthAdjustment;
	double adjustedPlayerPositionY = playerPositionComp.m_position.y /
		ApplicationParameters::k_heightAdjustment;

	{
		using namespace sf;
		float xPos = clickableActionArea.m_x - adjustedPlayerPositionX;
		float yPos = clickableActionArea.m_y - adjustedPlayerPositionY;
		if (xPos != 0 || yPos != 0)
		{
			rotationComp.m_angle = atan2(yPos, xPos);
		}
	}
	auto& sizeComp = m_rReg.emplace<SizeComp>(bowArrowEntity);
	auto& angle = rotationComp.m_angle;
	auto& widthAdjust = ApplicationParameters::k_widthAdjustment;
	auto& heightAdjust = ApplicationParameters::k_heightAdjustment;

	sizeComp.m_size.width = hypot(
		mk_arrowWidthUnits * widthAdjust * sin(angle),
		mk_arrowWidthUnits * heightAdjust * cos(angle));
	sizeComp.m_size.height = hypot(
		mk_arrowHeightUnits * heightAdjust * sin(angle),
		mk_arrowHeightUnits * widthAdjust * cos(angle));
}