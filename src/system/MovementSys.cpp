#include "system/MovementSys.hpp"

#include "component/tag/PlayerComp.hpp"

#include "component/functional/PositionComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Window.hpp>

#include <entt/entt.hpp>

MovementSys::MovementSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_speed(ApplicationParameters::k_playerMovementSpeed)
{ }

void MovementSys::Update()
{
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp) {
		{
			int& xPos = positionComp.m_position.x;
			int& yPos = positionComp.m_position.y;
			using namespace sf;
			if (Keyboard::isKeyPressed(Keyboard::A)) { xPos -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { yPos -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { xPos += m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { yPos += m_speed; }
		}
	});
}
