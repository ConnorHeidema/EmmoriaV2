#ifndef __SPRITE_COMP__
#define __SPRITE_COMP__

#include <string>

/**
 * This component should be used for anything that should link back to a sprite
 * this also gives the index of the file that should be used for the sprite (top left corner of sprite file)
 */
struct SpriteComp
{
	std::string m_filePath;
	int m_spriteIndex;
	int m_width;
	int m_height;

	SpriteComp()
		: m_filePath("")
		, m_spriteIndex(0)
		, m_width(100)
		, m_height(100)
	{}
};

#endif