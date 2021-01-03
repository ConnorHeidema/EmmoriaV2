#include "system/MovementSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/SpeedComp.hpp"
#include "component/functional/TrackingComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/PositionUtils.hpp"
#include "config/ConfigItems.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <entt/entt.hpp>

#include <math.h>

#include <cmath>

MovementSys::MovementSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void MovementSys::Update_()
{
	GoToDebugRoom_();
	UpdateLastPositions_();
	UpdatePlayerPosition_();
	UpdateArrowPosition_();
	UpdateBlobPosition_();
	DeleteRolloverObjects_();
}

void MovementSys::GoToDebugRoom_()
{
	static bool bBeenMoved = false; //quickfix and dirty
	if (!bBeenMoved && ConfigItems::m_setConfigItems.find("GoToTempRoom") != ConfigItems::m_setConfigItems.end())
	{
		m_rReg.view<PlayerComp, PositionComp, SpeedComp>().each([&](auto entity, auto& positionComp, auto& speedComp)
		{
			bBeenMoved = true;
			positionComp.m_position.x = ApplicationParameters::k_debugRoomX*ApplicationParameters::k_rightOfScreen + ApplicationParameters::k_rightOfScreen/2;
			positionComp.m_position.y = ApplicationParameters::k_debugRoomY*ApplicationParameters::k_bottomOfScreen + ApplicationParameters::k_bottomOfScreen/2;
		});
	}
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
		using namespace sf;
		float xPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::D)) -
					static_cast<int>(Keyboard::isKeyPressed(Keyboard::A)));
		float yPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::S)) -
					static_cast<int>(Keyboard::isKeyPressed(Keyboard::W)));
		if (xPos != 0 || yPos != 0)
		{
			float angle = atan2(yPos, xPos);
			PositionUtils::CalculateNewPosition(positionComp.m_position, speedComp.m_speed, angle);
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
		//PositionUtils::PrintPosition(positionComp.m_position, "Arrow");
		PositionUtils::CalculateNewPosition(positionComp.m_position, speedComp.m_speed, rotationComp.m_angle);
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
			//PositionUtils::PrintPosition(positionComp.m_position, "Blob");
			if (hypot(playerPositionComp.m_position.x - positionComp.m_position.x,
					playerPositionComp.m_position.y - positionComp.m_position.y) < trackingComp.m_sight)
			{
				float angle = atan2(
					playerPositionComp.m_position.y - positionComp.m_position.y,
					playerPositionComp.m_position.x - positionComp.m_position.x);
				PositionUtils::CalculateNewPosition(positionComp.m_position, speedComp.m_speed, angle);
			}
		});
	});
}


void MovementSys::DeleteRolloverObjects_()
{
	m_rReg.view<PositionComp, LastPositionComp>(entt::exclude<PlayerComp>).each([&](auto entity, auto& positionComp, auto& lastPositionComp)
	{
		int currentRegionX = (int)floor((double)positionComp.m_position.x / ApplicationParameters::k_rightOfScreen);
		int nextRegionX = (int)floor((double)lastPositionComp.m_lastPosition.x / ApplicationParameters::k_rightOfScreen);
		int currentRegionY = (int)floor((double)positionComp.m_position.y / ApplicationParameters::k_bottomOfScreen);
		int nextRegionY = (int)floor((double)lastPositionComp.m_lastPosition.y / ApplicationParameters::k_bottomOfScreen);

		if (currentRegionX != nextRegionX ||
			currentRegionY != nextRegionY)
		{
			m_rReg.destroy(entity);
		}
	});

}