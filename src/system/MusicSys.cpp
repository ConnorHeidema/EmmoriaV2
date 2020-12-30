#include "system/MusicSys.hpp"

#include <SFML/Audio/Music.hpp>

MusicSys::MusicSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void MusicSys::Update_()
{
	if (!m_pMusic)
	{
		m_pMusic = std::make_shared<sf::Music>();
		m_pMusic->openFromFile("media/DawnPillar.wav");
		m_pMusic->play();
		m_pMusic->setLoop(true);
	}
}