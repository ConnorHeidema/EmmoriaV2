#include "util/Mediamap.hpp"

std::unordered_map<Media_t, std::string> MediaMap::Create_map()
{
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] = std::experimental::filesystem::current_path().u8string() + "/media/intro.mp4";
	return m;
}

const std::unordered_map<Media_t, std::string> MediaMap::m_mediaMap =  MediaMap::Create_map();
