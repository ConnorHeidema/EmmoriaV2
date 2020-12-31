#include "util/Mediamap.hpp"


std::unordered_map<Media_t, std::string> Mediamap::Create_map()
{
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] = "media/intro.avi";
	m[Media_t::NEW_GAME_SELECTED] = "media/new_game_selected.avi";
	return m;
}

const std::unordered_map<Media_t, std::string> Mediamap::m_mediamap =  Mediamap::Create_map();
