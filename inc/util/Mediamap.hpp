#ifndef __MEDIA_MAP__
#define __MEDIA_MAP__

#include <unordered_map>
#include <string>
#include <experimental/filesystem>

enum class Media_t
{
	INTRO_MOVIE,
	NONE
};

struct MediaMap
{
    static std::unordered_map<Media_t, std::string> Create_map();
    static const std::unordered_map<Media_t, std::string> m_mediaMap;
};

#endif