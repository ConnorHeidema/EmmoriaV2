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
#include "component/functional/PositionComp.hpp"
#include "component/functional/ClickableComp.hpp"

#include <entt/entt.hpp>

#include <math.h>

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
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto& playerPositionComp)
		{
			m_rReg.view<ItemActionAreaComp, ClickableComp>().each([&](auto& clickableActionArea)
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

	m_rReg.emplace<SpeedComp>(bowArrowEntity).m_speed = 4;
	m_rReg.emplace<LifespanComp>(bowArrowEntity).m_framesToLive = 120;

	double xPos2 = 0;
	double yPos2 = 0;
	m_rReg.view<LocationComp>().each([&](auto& locationComp)
	{
		xPos2 += double(locationComp.xLocation) * ApplicationParameters::k_rightOfScreen;
		yPos2 += double(locationComp.yLocation) * ApplicationParameters::k_bottomOfScreen;
	});

	auto& bowArrowPositionComp = m_rReg.emplace<PositionComp>(bowArrowEntity); // should be changed to use helper mod
	bowArrowPositionComp.m_position.x = ((int)playerPositionComp.m_position.x % ApplicationParameters::k_rightOfScreen) + xPos2;
	bowArrowPositionComp.m_position.y = ((int)playerPositionComp.m_position.y % ApplicationParameters::k_bottomOfScreen) + yPos2;

	auto& renderable = m_rReg.emplace<RenderableComp>(bowArrowEntity);
	renderable.m_bRendered = false;
	auto& spriteComp = m_rReg.emplace<SpriteComp>(bowArrowEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + "Arrow" + ApplicationParameters::k_pictureExt;
	m_rReg.emplace<ArrowComp>(bowArrowEntity);

	//std::cout << "Creating arrow at (" << bowArrowPositionComp.m_position.x <<
	//	", " << bowArrowPositionComp.m_position.y << ")" << std::endl;

	m_rReg.emplace_or_replace<DeloadableComp>(bowArrowEntity);

	auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(bowArrowEntity);
	interactorComp.m_interactTypeList.insert(InteractType_t::ArrowComp_t);

	auto& rotationComp = m_rReg.emplace<RotationComp>(bowArrowEntity);

	double adjustedPlayerPositionX = playerPositionComp.m_position.x;
	double adjustedPlayerPositionY = playerPositionComp.m_position.y;

	{
		double xPos = clickableActionArea.m_x * ApplicationParameters::k_widthAdjustment - adjustedPlayerPositionX;
		double yPos = clickableActionArea.m_y * ApplicationParameters::k_heightAdjustment - adjustedPlayerPositionY;
		m_rReg.view<LocationComp>().each([&](auto& locationComp)
		{
			xPos += double(locationComp.xLocation) * ApplicationParameters::k_rightOfScreen;
			yPos += double(locationComp.yLocation) * ApplicationParameters::k_bottomOfScreen;
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

	sizeComp.m_size.width = uint32_t(hypot(
		sin(angle) * mk_arrowWidthUnits * widthAdjust,
		cos(angle) * mk_arrowWidthUnits * heightAdjust));
	sizeComp.m_size.height = uint32_t(hypot(
		sin(angle) * mk_arrowHeightUnits * heightAdjust,
		cos(angle) * mk_arrowHeightUnits * widthAdjust));
}