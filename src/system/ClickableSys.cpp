#include "system/ClickableSys.hpp"

#include "component/PositionComp.hpp"
#include "component/ClickableComp.hpp"
#include "component/SizeComp.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

void ClickableSys::Update(entt::registry& reg)
{
	m_xMousePosition = sf::Mouse::getPosition().x;
	m_yMousePosition = sf::Mouse::getPosition().y;

	reg.view<PositionComp, SizeComp, ClickableComp>().each([&](auto entity, auto &posComp, auto &sizeComp) {
		if (IsCollisionDetected_(
			posComp.position.x,
			posComp.position.y,
			sizeComp.size.width,
			sizeComp.size.height))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "Left clicked" << std::endl;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				std::cout << "Right clicked" << std::endl;
			}
			std::cout << "Mouse position at : (" +
				std::to_string(sf::Mouse::getPosition().x) + ", " +
				std::to_string(sf::Mouse::getPosition().y) + ")" << std::endl;
		}
	});
}

bool ClickableSys::IsCollisionDetected_(int const& left, int const& top, int const& width, int const& height)
{
	return
		left < m_xMousePosition &&
		left + width > m_xMousePosition &&
		top < m_yMousePosition &&
		top + height > m_yMousePosition;
}