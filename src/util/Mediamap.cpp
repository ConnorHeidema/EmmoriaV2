#include "util/Mediamap.hpp"

std::unordered_map<Media_t, std::string> Mediamap::Create_map()
{
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] = std::experimental::filesystem::current_path().u8string() + "/media/intro.avi";
	return m;
}

const std::unordered_map<Media_t, std::string> Mediamap::m_mediamap =  Mediamap::Create_map();