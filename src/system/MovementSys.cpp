#include "system/MovementSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"

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
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp) {
		{
			auto& lastPositionComp = m_rReg.get_or_emplace<LastPositionComp>(entity);
			lastPositionComp.m_lastPosition.x = positionComp.m_position.x;
			lastPositionComp.m_lastPosition.y = positionComp.m_position.y;

			using namespace sf;
			float xPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::D)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::A))) * m_speed;
			float yPos = (static_cast<int>(Keyboard::isKeyPressed(Keyboard::S)) -
						static_cast<int>(Keyboard::isKeyPressed(Keyboard::W))) * m_speed;
			if (xPos != 0 || yPos != 0)
			{
				float angle = atan2(yPos, xPos);
				positionComp.m_position.x += m_speed * cos(angle);
				positionComp.m_position.y += m_speed * sin(angle);
			}
		}
	});
}
