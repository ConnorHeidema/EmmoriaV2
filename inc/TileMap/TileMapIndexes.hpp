#ifndef __TILE_MAP_INDEXES__
#define __TILE_MAP_INDEXES__

#include <unordered_map>

#define ALL_DAWN_PILLAR_MACRO(m) \
	m(DAWN_PILLAR_GRASS_1) \
	m(DAWN_PILLAR_GRASS_2) \
	m(DAWN_PILLAR_GRASS_3) \
	m(DAWN_PILLAR_GRASS_4) \
	m(DAWN_PILLAR_CARPET) \
	m(DAWN_PILLAR_INACCESSIBLE) \
	m(DAWN_PILLAR_RIGHT_WALL) \
	m(DAWN_PILLAR_GROUND) \
	m(DAWN_PILLAR_BOTTOM_WALL) \
	m(DAWN_PILLAR_LEFT_WALL) \
	m(DAWN_PILLAR_TOP_WALL) \
	m(DAWN_PILLAR_HOLE) \
	m(DAWN_PILLAR_STAIRS) \
	m(DAWN_PILLAR_SIGN)

#define commaMacro(name) name,

#define REGION_ENUM(enum_name, macro) \
enum enum_name \
{ \
	macro(commaMacro) \
	NUM_##enum_name \
};

REGION_ENUM(DawnPillar, ALL_DAWN_PILLAR_MACRO)

enum Blob
{
	BLOB_1,
	BLOB_2,
	BLOB_3,
	BLOB_4,
	NUM_BLOB
};

enum Player
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	PLAYER_5,
	PLAYER_6,
	PLAYER_7,
	PLAYER_8,
	PLAYER_9,
	PLAYER_10,
	PLAYER_11,
	PLAYER_12,
	PLAYER_13,
	PLAYER_14,
	PLAYER_15,
	PLAYER_16,
	NUM_PLAYER
};

class TileMapIndexes
{
public:
	static std::unordered_map<std::string, int> stringToEnumTileMap;
	static std::unordered_map<int, std::string> intToStringTileMap;
	static int const k_invalidInt;
	static std::string const k_invalidString;
};

#endif