#include "system/MovementSys.hpp"

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
	// int const& speed = ApplicationParameters::k_playerMovementSpeed;
	// m_rReg.view<PlayerComp, PositionComp>().each([&](auto entity, auto &posComp) {
	// 	{
	// 		using namespace sf;
	// 		if (Keyboard::isKeyPressed(Keyboard::A)) { posComp.position.x -= m_speed; }
	// 		if (Keyboard::isKeyPressed(Keyboard::W)) { posComp.position.y -= m_speed; }
	// 		if (Keyboard::isKeyPressed(Keyboard::D)) { posComp.position.x += m_speed; }
	// 		if (Keyboard::isKeyPressed(Keyboard::S)) { posComp.position.y += m_speed; }
	// 	}
	// });
}
