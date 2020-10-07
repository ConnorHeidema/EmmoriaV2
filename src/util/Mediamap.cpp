#include "util/Mediamap.hpp"

std::unordered_map<Media_t, std::string> Mediamap::Create_map()
{
	
	#ifdef __linux__ 
		using namespace std::experimental;
	#elif _WIN32
		using namespace std;
	#else

	#endif
	std::unordered_map<Media_t, std::string> m;
	m[Media_t::INTRO_MOVIE] = filesystem::current_path().u8string() + "/media/intro.avi";
	m[Media_t::NEW_GAME_SELECTED] = filesystem::current_path().u8string() + "/media/new_game_selected.avi";
	return m;
}

const std::unordered_map<Media_t, std::string> Mediamap::m_mediamap =  Mediamap::Create_map();
