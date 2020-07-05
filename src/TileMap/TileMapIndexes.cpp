#include "TileMap/TileMapIndexes.hpp"

#include <string>

#define TILEMAP_STRING_TO_TYPE_MAPPING(name) { #name , name },
#define TILEMAP_TYPE_TO_STRING_MAPPING(name) { name, #name },

int const TileMapIndexes::k_invalidInt = -1;
std::string const TileMapIndexes::k_invalidString = "Invalid";

std::unordered_map<std::string, int> TileMapIndexes::stringToEnumTileMap =
{
	ALL_DAWN_PILLAR_MACRO(TILEMAP_STRING_TO_TYPE_MAPPING)
	{ TileMapIndexes::k_invalidString, TileMapIndexes::k_invalidInt }
};


std::unordered_map<int, std::string> TileMapIndexes::intToStringTileMap =
{
	ALL_DAWN_PILLAR_MACRO(TILEMAP_TYPE_TO_STRING_MAPPING)
	{ TileMapIndexes::k_invalidInt, TileMapIndexes::k_invalidString }
};
