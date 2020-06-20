#include "core/Application.hpp"

#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
#include "system/MovieRenderSys.hpp"
#include "system/GameRenderSys.hpp"

#include "util/ApplicationParameters.hpp"

#include <memory>
#include <string>

Application::Application()
	: m_renderWindow(nullptr)
{ }

bool Application::Start()
{
	Initialize_();
	while (m_renderWindow->isOpen()) { {RunLoop_();}; }
	return true;
}

void Application::Initialize_()
{
	m_renderWindow = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(
				ApplicationParameters::k_screenWidth,
				ApplicationParameters::k_screenHeight),
			ApplicationParameters::k_windowName,
			sf::Style::Fullscreen);
	m_renderWindow->setFramerateLimit(ApplicationParameters::k_framerate);

	m_movementSys.Initialize(m_reg);
	m_printMovementSys.Initialize(m_reg);
	m_movieRenderSystem.Initialize(m_reg);
	m_gameRenderSystem.Initialize(m_reg);
}


void Application::RunLoop_()
{
	m_renderWindow->clear();
	m_movementSys.Update(m_reg);
	m_printMovementSys.Update(m_reg);
	m_movieRenderSystem.Update(m_reg, m_renderWindow);
	m_gameRenderSystem.Update(m_reg, m_renderWindow);
	CheckForEvents_();
	m_renderWindow->display();
}

void Application::CheckForEvents_()
{
	sf::Event event;
	while (m_renderWindow->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: m_renderWindow->close(); break;
			case sf::Event::GainedFocus: break;
			case sf::Event::LostFocus:  break;
			default: break;
		}
	}
}