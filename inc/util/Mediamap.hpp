#ifndef __MEDIA_MAP__
#define __MEDIA_MAP__

#include <unordered_map>
#include <string>

#ifdef __linux__ 
	#include <experimental/filesystem>
#elif _WIN32
	#include <filesystem>
#else

#endif

enum class Media_t
{
	INTRO_MOVIE,
	NEW_GAME_SELECTED,
	NONE
};

struct Mediamap
{
    static std::unordered_map<Media_t, std::string> Create_map();
    static const std::unordered_map<Media_t, std::string> m_mediamap;
};

#endif