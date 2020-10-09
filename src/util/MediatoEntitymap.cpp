#include "util/MediatoEntitymap.hpp"
#include "config/ConfigItems.hpp"

std::unordered_map<Media_t, std::string> MediatoEntitymap::Create_map()
{
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] =
		ConfigItems::m_setConfigItems.find("JumpToGame") == ConfigItems::m_setConfigItems.end() ?
			"intro/loadfiles.txt" :
			"Files/0,0";
	m[Media_t::NEW_GAME_SELECTED] = "intro/beginning.txt"; // this isn't known necessarily. potential design flaw..
	return m;
}

std::unordered_map<Media_t, std::string> MediatoEntitymap::m_mediatoEntitymap = {};
