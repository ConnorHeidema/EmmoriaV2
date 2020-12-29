#include "system/BowSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/InteractorComp.hpp"
#include "component/functional/SpeedComp.hpp"
#include "component/functional/LocationComp.hpp"
#include "component/functional/LifespanComp.hpp"

#include "component/InteractType.hpp"

#include "util/Mediamap.hpp"

#include <entt/entt.hpp>

#include <math.h>
#include <iostream>

const int BowSys::mk_frequency = 60;
const int BowSys::mk_arrowWidthUnits = 2;
const int BowSys::mk_arrowHeightUnits = 5;

BowSys::BowSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_bowFrequencyLatch(mk_frequency)
{ }

void BowSys::Update_()
{
	bool playerBowExists = false;

	m_rReg.view<PlayerComp, BowComp>().each([&](){
		playerBowExists = true;
	});

	if (m_bowFrequencyLatch.Peek() && playerBowExists)
	{
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& playerPositionComp)
		{
			bool bPerformAction = false;
			m_rReg.view<ItemActionAreaComp, ClickableComp>().each([&](auto entity, auto& clickableActionArea)
			{
				if (clickableActionArea.m_bLeftDown)
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

	auto& speedComp = m_rReg.emplace<SpeedComp>(bowArrowEntity);
	speedComp.m_speed = 4;

	auto& lifespanComp = m_rReg.emplace<LifespanComp>(bowArrowEntity);
	lifespanComp.m_framesToLive = 120;

	double xPos2 = 0;
	double yPos2 = 0;
	m_rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		xPos2 += locationComp.xLocation * ApplicationParameters::k_rightOfScreen;
		yPos2 += locationComp.yLocation * ApplicationParameters::k_bottomOfScreen;
	});

	auto& bowArrowPositionComp = m_rReg.emplace<PositionComp>(bowArrowEntity);
	bowArrowPositionComp.m_position.x = ((int)playerPositionComp.m_position.x % ApplicationParameters::k_rightOfScreen) + xPos2;
	bowArrowPositionComp.m_position.y = ((int)playerPositionComp.m_position.y % ApplicationParameters::k_bottomOfScreen) + yPos2;

	auto& renderable = m_rReg.emplace<RenderableComp>(bowArrowEntity);
	renderable.m_bRendered = false;
	auto& spriteComp = m_rReg.emplace<SpriteComp>(bowArrowEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + "Arrow" + ApplicationParameters::k_pictureExt;
	m_rReg.emplace<ArrowComp>(bowArrowEntity);

	std::cout << "Creating arrow at (" << bowArrowPositionComp.m_position.x <<
		", " << bowArrowPositionComp.m_position.y << ")" << std::endl;

	m_rReg.emplace_or_replace<DeloadableComp>(bowArrowEntity);

	auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(bowArrowEntity);
	interactorComp.m_interactTypeList.insert(InteractType_t::ArrowComp_t);

	auto& rotationComp = m_rReg.emplace<RotationComp>(bowArrowEntity);

	double adjustedPlayerPositionX = playerPositionComp.m_position.x;
	double adjustedPlayerPositionY = playerPositionComp.m_position.y;

	{
		using namespace sf;
		double xPos = clickableActionArea.m_x * ApplicationParameters::k_widthAdjustment - adjustedPlayerPositionX;
		double yPos = clickableActionArea.m_y * ApplicationParameters::k_heightAdjustment - adjustedPlayerPositionY;
		m_rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
		{
			xPos += locationComp.xLocation * ApplicationParameters::k_rightOfScreen;
			yPos += locationComp.yLocation * ApplicationParameters::k_bottomOfScreen;
		});
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