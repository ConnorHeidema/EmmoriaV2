#include "core/Application.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"

#include <iostream>
#include <memory>

Application::Application()
{ }

bool Application::Start()
{
	m_movie.openFromFile("/media/connor/DATA/Documents/git/Emmoria/media/intro.mp4");
	auto gameWindow(sf::RenderWindow
			(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),
			"Test",
			sf::Style::Fullscreen));
	gameWindow.setFramerateLimit(60);

	auto player = m_reg.create();
	m_reg.emplace<PlayerComp>(player);
	auto& rMovementComponent = m_reg.emplace<PositionComp>(player);
	rMovementComponent.position.x = 100;
	rMovementComponent.position.y = 200;
	m_reg.emplace<RenderableComp>(player);
	m_movie.play();
	while (gameWindow.isOpen()) { while(true) {RunLoop_(gameWindow);}; }

	return true;
}

void Application::RunLoop_(sf::RenderWindow& gameWindow)
{
	m_movie.update();
	gameWindow.clear();
	gameWindow.draw(m_movie);
	m_movementSys.Update(m_reg);
	m_printMovementSys.Update(m_reg);
	m_renderSystem.Update(m_reg, gameWindow);
	gameWindow.display();
	CheckForEvents_(gameWindow);
}

void Application::CheckForEvents_(sf::RenderWindow& gameWindow)
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: gameWindow.close(); break;
			case sf::Event::GainedFocus: break;
			case sf::Event::LostFocus:  break;
			default: break;
		}
	}
}