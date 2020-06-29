#include "system/MovementSys.hpp"

#include "component/tag/PlayerComp.hpp"

#include "component/functional/PositionComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Graphics.hpp>

#include <entt/entt.hpp>

MovementSys::MovementSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_speed(ApplicationParameters::k_playerMovementSpeed)
{ }

void MovementSys::Update()
{
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto& positionComp) {
		{
			using namespace sf;
			if (Keyboard::isKeyPressed(Keyboard::A)) { positionComp.m_position.x -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { positionComp.m_position.y -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { positionComp.m_position.x += m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { positionComp.m_position.y += m_speed; }
		}
	});
}
