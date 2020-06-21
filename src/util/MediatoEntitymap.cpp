#include "util/MediatoEntitymap.hpp"

std::unordered_map<Media_t, std::string> MediatoEntitymap::Create_map()
{
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] = "intro/loadfiles.txt";
	m[Media_t::NEW_GAME_SELECTED] = "intro/beginning.txt"; // this isn't known necessarily. potential design flaw..
	return m;
}

const std::unordered_map<Media_t, std::string> MediatoEntitymap::m_mediatoEntitymap =  MediatoEntitymap::Create_map();
