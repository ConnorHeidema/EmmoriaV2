#include "core/Application.hpp"

#include "util/ApplicationParameters.hpp"

#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
#include "system/MovieRenderSys.hpp"
#include "system/GameRenderSys.hpp"
#include "system/LoadingSys.hpp"
#include "system/ClickableSys.hpp"
#include "system/DialogSys.hpp"

Application::Application()
	: m_reg()
	, m_renderWindow(
		sf::VideoMode(
				ApplicationParameters::k_screenWidth,
				ApplicationParameters::k_screenHeight),
			ApplicationParameters::k_windowName,
			sf::Style::Fullscreen)
	, m_pSystems
	{
		std::make_unique<MovementSys>(m_reg),
		std::make_unique<PrintMovementSys>(m_reg),
		std::make_unique<MovieRenderSys>(m_reg, m_renderWindow),
		std::make_unique<GameRenderSys>(m_reg, m_renderWindow),
		std::make_unique<LoadingSys>(m_reg),
		std::make_unique<ClickableSys>(m_reg),
		std::make_unique<DialogSys>(m_reg, m_renderWindow)
	}
{ }

bool Application::Start()
{
	Initialize_();
	while (m_renderWindow.isOpen()) { {RunLoop_();}; }
	return true;
}

void Application::Initialize_()
{
	m_renderWindow.setFramerateLimit(ApplicationParameters::k_framerate);
}

void Application::RunLoop_()
{
	m_renderWindow.clear();
	for (auto system : m_pSystems) { system->Update(); }
	m_renderWindow.display();
	CheckForEvents_();
}

void Application::CheckForEvents_()
{
	sf::Event event;
	while (m_renderWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: m_renderWindow.close(); break;
			case sf::Event::GainedFocus: break;
			case sf::Event::LostFocus:  break;
			default: break;
		}
	}
}