#include "system/MusicSys.hpp"

#include "component/functional/SoundComp.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <entt/entt.hpp>

MusicSys::MusicSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{
	m_pSound = std::make_shared<sf::Sound>();
	m_pSoundBuffer = std::make_shared<sf::SoundBuffer>();
}

void MusicSys::Update_()
{
	m_rReg.view<SoundComp>().each([&](
		auto entity,
		auto& soundComp)
	{
		m_pSoundBuffer->loadFromFile("media/" + soundComp.m_sound);
		m_pSound->setBuffer(*m_pSoundBuffer);
		m_pSound->play();
		m_rReg.destroy(entity);
	});
	if (!m_pMusic)
	{
		m_pMusic = std::make_shared<sf::Music>();
		m_pMusic->openFromFile("media/DawnPillar.wav");
		m_pMusic->setVolume(1);
		m_pMusic->play();
		m_pMusic->setLoop(true);
	}
}