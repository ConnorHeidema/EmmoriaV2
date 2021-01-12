#include "util/SFMLUtils.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

int SFMLUtils::s_wheelMovement = 0;
int SFMLUtils::testNum = 0;

void SFMLUtils::ResetUserSFMLEventState()
{
	s_wheelMovement = 0;
}

bool SFMLUtils::ProcessSFMLEvents(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::MouseWheelScrolled:
		{
			s_wheelMovement = static_cast<int>(event.mouseWheelScroll.delta);
			return true;
		}
		default:
		{
			return false;
		}
	}
}