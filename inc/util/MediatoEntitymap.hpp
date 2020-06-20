#ifndef __MEDIA_TO_ENTITY_MAP__
#define __MEDIA_TO_ENTITY_MAP__

#include "util/Mediamap.hpp"
#include "util/Entitymap.hpp"

#include <unordered_map>
#include <string>
#include <experimental/filesystem>

struct MediatoEntitymap
{
    static std::unordered_map<Media_t, std::string> Create_map();
    static const std::unordered_map<Media_t, std::string> m_mediatoEntitymap;
};

#endif