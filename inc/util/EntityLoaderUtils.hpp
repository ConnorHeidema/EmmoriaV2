#ifndef __ENTITY_LOADER_UTILS__
#define __ENTITY_LOADER_UTILS__

#include "util/Mediamap.hpp"
#include "util/Entitymap.hpp"

#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

class EntityLoaderUtils
{
public:
	static int GetTextWidth(std::string text, int height);
};

#endif