#ifndef __MUSIC_SYS__
#define __MUSIC_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

#include <memory>

namespace sf { class Music; }
namespace sf { class Sound; }
namespace sf { class SoundBuffer; }

/**
 * This system handles interactions between 2 objects
 */
class MusicSys
	: public System
{
public:
	MusicSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	std::shared_ptr<sf::Music> m_pMusic;
	std::shared_ptr<sf::Sound> m_pSound;
	std::shared_ptr<sf::SoundBuffer> m_pSoundBuffer;
	entt::registry& m_rReg;
	std::string m_lastMusic;
};

#endif
