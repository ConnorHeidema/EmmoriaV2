#include "core/Application.hpp"

#include "system/System.hpp"
#include "config/ConfigItems.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/SystemList.hpp"

#include "util/MediatoEntitymap.hpp"
#include "util/SFMLUtils.hpp"

#include <SFML/Window/Event.hpp>

Application::Application()
	: m_reg()
	, m_renderWindow(
		sf::VideoMode(
				ApplicationParameters::k_screenWidth,
				ApplicationParameters::k_screenHeight),
			ApplicationParameters::k_windowName,
			sf::Style::Fullscreen)
	, m_kOnlyWhenFocused("OnlyWhenFocused")
{ }

bool Application::Start()
{
	Initialize_();
	while (m_renderWindow.isOpen()) { {RunLoop_();}; }
	return true;
}

void Application::Initialize_()
{
    ConfigItems::LoadConfigFile("data/Config/config.ini");
	MediatoEntitymap::m_mediatoEntitymap = MediatoEntitymap::Create_map();
	m_renderWindow.setFramerateLimit(ApplicationParameters::k_framerate);
	SystemList::m_pSystemList = SystemList::CreateSystemList(m_reg, m_renderWindow);
}

void Application::RunLoop_()
{
	CheckForEvents_();
	m_renderWindow.clear();
	for (auto& system : SystemList::m_pSystemList)
	{
		if (m_renderWindow.hasFocus() || UpdateWhenNotFocused_())
		{
			system->Update();
		}
	}
	m_renderWindow.display();
}

void Application::CheckForEvents_()
{
	SFMLUtils::ResetUserSFMLEventState();
	sf::Event event;
	while (m_renderWindow.pollEvent(event))
	{
		if (SFMLUtils::ProcessSFMLEvents(event))
			break;
		switch (event.type)
		{
			case sf::Event::Closed: m_renderWindow.close(); break;
			case sf::Event::GainedFocus: break;
			case sf::Event::LostFocus:  break;
			default: break;
		}
	}
}

bool Application::UpdateWhenNotFocused_()
{
	return ConfigItems::m_setConfigItems.find(m_kOnlyWhenFocused) ==
		ConfigItems::m_setConfigItems.end();
}
