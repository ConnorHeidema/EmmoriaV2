#include "system/MovementSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LastPositionComp.hpp"
#include "component/functional/PositionComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Window.hpp>

#include <entt/entt.hpp>

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
			float& xPos = positionComp.m_position.x;
			float& yPos = positionComp.m_position.y;
			lastPositionComp.m_lastPosition.x = xPos;
			lastPositionComp.m_lastPosition.y = yPos;
			using namespace sf;
			if (Keyboard::isKeyPressed(Keyboard::A)) { xPos -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { yPos -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { xPos += m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { yPos += m_speed; }
		}
	});
}
