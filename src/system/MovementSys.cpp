#include "system/MovementSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/SpeedComp.hpp"
#include "component/functional/TrackingComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Window.hpp>

#include <entt/entt.hpp>

#include <math.h>

MovementSys::MovementSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void MovementSys::Update_()
{
	UpdateLastPositions_();
	UpdatePlayerPosition_();
	UpdateArrowPosition_();
	UpdateBlobPosition_();
}

void MovementSys::UpdateLastPositions_()
{
	m_rReg.view<PositionComp>().each([&](auto entity, auto& positionComp) {
		auto& lastPositionComp = m_rReg.get_or_emplace<LastPositionComp>(entity);
		lastPositionComp.m_lastPosition.x = positionComp.m_position.x;
		lastPositionComp.m_lastPosition.y = positionComp.m_position.y;
	});
}

void MovementSys::UpdatePlayerPosition_()
{
	m_rReg.view<PlayerComp, PositionComp, SpeedComp>().each([&](auto entity, auto& positionComp, auto& speedComp) {
		{
			using namespace sf;
			float xPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::D)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::A)));
			float yPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::S)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::W)));
			if (xPos != 0 || yPos != 0)
			{
				float angle = atan2(yPos, xPos);
				positionComp.m_position.x += speedComp.m_speed * cos(angle);
				positionComp.m_position.y += speedComp.m_speed * sin(angle);
			}
		}
	});
}

void MovementSys::UpdateArrowPosition_()
{
	m_rReg.view<ArrowComp, PositionComp, RotationComp, SpeedComp>().each([&](
		auto entity,
		auto& positionComp,
		auto& rotationComp,
		auto& speedComp)
	{
		positionComp.m_position.x += speedComp.m_speed * cos(rotationComp.m_angle);
		positionComp.m_position.y += speedComp.m_speed * sin(rotationComp.m_angle);
		if (positionComp.m_position.x < 0 || positionComp.m_position.x > ApplicationParameters::k_rightOfScreen ||
			positionComp.m_position.y < 0 || positionComp.m_position.y > ApplicationParameters::k_bottomOfScreen)
		{
			m_rReg.destroy(entity);
		}
	});
}

void MovementSys::UpdateBlobPosition_()
{

	m_rReg.view<PlayerComp, PositionComp>().each([&](auto playerEntity, auto& playerPositionComp)
	{
		m_rReg.view<PositionComp, SpeedComp, TrackingComp>().each([&](
			auto blobEntity,
			auto& positionComp,
			auto& speedComp,
			auto& trackingComp)
		{
			if (std::abs(playerPositionComp.m_position.x - positionComp.m_position.x) < trackingComp.m_sight &&
				std::abs(playerPositionComp.m_position.y - positionComp.m_position.y) < trackingComp.m_sight)
			{
				float angle = atan2(
					playerPositionComp.m_position.y - positionComp.m_position.y,
					playerPositionComp.m_position.x - positionComp.m_position.x);
				positionComp.m_position.x += speedComp.m_speed * cos(angle);
				positionComp.m_position.y += speedComp.m_speed * sin(angle);
			}
		});
	});
}