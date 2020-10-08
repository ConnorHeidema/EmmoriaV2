#include "system/MovementSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RotationComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Window.hpp>

#include <entt/entt.hpp>

#include <math.h>

MovementSys::MovementSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_speed(ApplicationParameters::k_playerMovementSpeed)
{ }

void MovementSys::Update_()
{
	m_rReg.view<PositionComp>().each([&](auto entity, auto& positionComp) {
		auto& lastPositionComp = m_rReg.get_or_emplace<LastPositionComp>(entity);
		lastPositionComp.m_lastPosition.x = positionComp.m_position.x;
		lastPositionComp.m_lastPosition.y = positionComp.m_position.y;
	});
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp) {
		{
			using namespace sf;
			float xPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::D)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::A)));
			float yPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::S)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::W)));
			if (xPos != 0 || yPos != 0)
			{
				float angle = atan2(yPos, xPos);
				positionComp.m_position.x += m_speed * cos(angle);
				positionComp.m_position.y += m_speed * sin(angle);
			}
		}
	});


	m_rReg.view<ArrowComp, PositionComp, RotationComp>().each([&](auto entity, auto& positionComp, auto& rotationComp)
	{
		positionComp.m_position.x += 4 * cos(rotationComp.m_angle);
		positionComp.m_position.y += 4 * sin(rotationComp.m_angle);
		if (positionComp.m_position.x < 0 || positionComp.m_position.x > ApplicationParameters::k_rightOfScreen ||
			positionComp.m_position.y < 0 || positionComp.m_position.y > ApplicationParameters::k_bottomOfScreen)
		{
			m_rReg.destroy(entity);
		}
	});
}
