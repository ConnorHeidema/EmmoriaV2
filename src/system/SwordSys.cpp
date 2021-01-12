#include "system/SwordSys.hpp"

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

#include "component/functional/LinkComp.hpp"

#include <entt/entt.hpp>

#include <math.h>
#include <iostream>

const int SwordSys::mk_frequency = 60;
const int SwordSys::mk_arrowWidthUnits = 2;
const int SwordSys::mk_arrowHeightUnits = 5;

SwordSys::SwordSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_swordFrequencyLatch(30)
{ }

void SwordSys::Update_()
{
	bool playerSwordExists = false;
	m_rReg.view<PlayerComp, SwordHolderComp>().each([&](){
		playerSwordExists = true;
	});

	if (m_swordFrequencyLatch.Peek() && playerSwordExists)
	{
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto& playerPositionComp)
		{
			m_rReg.view<ItemActionAreaComp, ClickableComp>().each([&](auto& clickableActionArea)
			{
				if (clickableActionArea.m_bLeftDown)
				{
					CreateSword_(playerPositionComp, clickableActionArea);
					m_swordFrequencyLatch.Reset();
				}
			});
		});
	}
	else
	{
		m_swordFrequencyLatch.CheckLatch();
	}
}

void SwordSys::CreateSword_(
		PositionComp& playerPositionComp,
		ClickableComp& clickableActionArea)
{
	auto swordEntity = m_rReg.create();

	m_rReg.emplace<SpeedComp>(swordEntity).m_speed = 2;
	m_rReg.emplace<LifespanComp>(swordEntity).m_framesToLive = 30;// 30 used in movement sys as well rn

	double xPos2 = 0;
	double yPos2 = 0;
	m_rReg.view<LocationComp>().each([&](auto& locationComp)
	{
		xPos2 += double(locationComp.xLocation) * ApplicationParameters::k_rightOfScreen;
		yPos2 += double(locationComp.yLocation) * ApplicationParameters::k_bottomOfScreen;
	});

	m_rReg.emplace<PositionComp>(swordEntity) =
	{
		((int)playerPositionComp.m_position.x % ApplicationParameters::k_rightOfScreen) + xPos2,
		((int)playerPositionComp.m_position.y % ApplicationParameters::k_bottomOfScreen) + yPos2
	};

	m_rReg.emplace<RenderableComp>(swordEntity).m_bRendered = false;
	m_rReg.emplace<SpriteComp>(swordEntity).m_filePath = ApplicationParameters::k_spritePath + "Sword" + ApplicationParameters::k_pictureExt;

	m_rReg.emplace<SwordComp>(swordEntity);

	//std::cout << "Creating arrow at (" << bowArrowPositionComp.m_position.x <<
	//	", " << bowArrowPositionComp.m_position.y << ")" << std::endl;

	m_rReg.emplace_or_replace<DeloadableComp>(swordEntity);

	auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(swordEntity);
	interactorComp.m_interactTypeList.insert(InteractType_t::SwordComp_t);

	auto& rotationComp = m_rReg.emplace<RotationComp>(swordEntity);

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
	auto& sizeComp = m_rReg.emplace<SizeComp>(swordEntity);
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