#include "system/MovementSys.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Graphics.hpp>

MovementSys::MovementSys()
	: m_speed(ApplicationParameters::k_playerMovementSpeed)
{ }

void MovementSys::Update(entt::registry& reg)
{
	int const& speed = ApplicationParameters::k_playerMovementSpeed;
	reg.view<PlayerComp, PositionComp>().each([&](auto entity, auto &posComp) {
		{
			using namespace sf;
			if (Keyboard::isKeyPressed(Keyboard::A)) { posComp.position.x -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { posComp.position.y -= m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { posComp.position.x += m_speed; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { posComp.position.y += m_speed; }
		}
	});
}
