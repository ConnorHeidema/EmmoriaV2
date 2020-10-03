#include "core/Application.hpp"

#include "system/System.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/SystemList.hpp"

Application::Application()
	: m_reg()
	, m_renderWindow(
		sf::VideoMode(
				ApplicationParameters::k_screenWidth,
				ApplicationParameters::k_screenHeight),
			ApplicationParameters::k_windowName,
			sf::Style::Fullscreen)
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
	SystemList::m_pSystemList = SystemList::CreateSystemList(m_reg, m_renderWindow);
}

void Application::RunLoop_()
{
	m_renderWindow.clear();
	for (auto system : SystemList::m_pSystemList) { system->Update(); }
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
