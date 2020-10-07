#include "system/BowSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/PositionComp.hpp"
#include "component/functional/ClickableComp.hpp"
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
	, m_bowCllickLatch(30)
{ }

void BowSys::Update_()
{
	if (m_bowCllickLatch == 0)
		m_bowCllickLatch = mk_frequency;

	if (m_bowCllickLatch == mk_frequency)
	{
		m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& playerPositionComp)
		{
			bool bPerformAction = false;
			m_rReg.view<ItemActionAreaComp, ClickableComp>().each([&](auto entity, auto& clickableActionArea)
			{
				if (clickableActionArea.m_bLeftClicked)
				{
					std::cout << "performing action:" << m_bowCllickLatch << std::endl;
					auto bowArrowEntity = m_rReg.create();
					auto& bowArrowPositionComp = m_rReg.emplace<PositionComp>(bowArrowEntity);
					bowArrowPositionComp.m_position.x = playerPositionComp.m_position.x;
					bowArrowPositionComp.m_position.y = playerPositionComp.m_position.y;
					auto& renderable = m_rReg.emplace<RenderableComp>(bowArrowEntity);
					renderable.m_bRendered = false;
					auto& spriteComp = m_rReg.emplace<SpriteComp>(bowArrowEntity);
					spriteComp.m_filePath = ApplicationParameters::k_spritePath + "Arrow" + ApplicationParameters::k_pictureExt;
					m_rReg.emplace<ArrowComp>(bowArrowEntity);

					auto& interactorComp = m_rReg.get_or_emplace<InteractorComp>(bowArrowEntity);
					interactorComp.m_interactType.emplace_back(InteractType_t::ArrowComp_t);

					auto& rotationComp = m_rReg.emplace<RotationComp>(bowArrowEntity);

					std::cout << "PLAYER POSITION: (" << playerPositionComp.m_position.x
						<< ", " << playerPositionComp.m_position.y << ")" << std::endl;
					double adjustedPlayerPositionX = playerPositionComp.m_position.x / ApplicationParameters::k_widthAdjustment;
					double adjustedPlayerPositionY = playerPositionComp.m_position.y / ApplicationParameters::k_heightAdjustment;

					using namespace sf;
					float xPos = clickableActionArea.m_x - adjustedPlayerPositionX;
					float yPos = clickableActionArea.m_y - adjustedPlayerPositionY;
					if (xPos != 0 || yPos != 0)
					{
						rotationComp.m_angle = atan2(yPos, xPos);
					}

					auto& sizeComp = m_rReg.emplace<SizeComp>(bowArrowEntity);
					sizeComp.m_size.width =
						std::sqrt(
							std::pow(
								mk_arrowWidthUnits * ApplicationParameters::k_widthAdjustment * sin(rotationComp.m_angle),2) +
							std::pow(
								mk_arrowWidthUnits * ApplicationParameters::k_heightAdjustment * cos(rotationComp.m_angle),2));
					sizeComp.m_size.height =
						std::sqrt(
							std::pow(
								mk_arrowHeightUnits * ApplicationParameters::k_heightAdjustment * sin(rotationComp.m_angle), 2) +
							std::pow(
								mk_arrowHeightUnits * ApplicationParameters::k_widthAdjustment * cos(rotationComp.m_angle),2));
					std::cout << "(" << sizeComp.m_size.width << ", " << sizeComp.m_size.height << ")" << std::endl;

					m_bowCllickLatch--;
				}
			});
		});
	}
	else
	{
		m_bowCllickLatch--;
	}
	m_rReg.view<ArrowComp, PositionComp, RotationComp>().each([&](auto entity, auto& positionComp, auto& rotationComp)
	{
		positionComp.m_position.x += 4 * cos(rotationComp.m_angle);
		positionComp.m_position.y += 4 * sin(rotationComp.m_angle);
	});
}
