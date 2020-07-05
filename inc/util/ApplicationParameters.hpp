#ifndef __APPLICATION_PARAMETERS__
#define __APPLICATION_PARAMTERES__

#include <string>

struct ApplicationParameters
{
	static int const k_screenWidth;
	static int const k_screenHeight;
	static int const k_framerate;

	static std::string const k_windowName;
	static std::string const k_dataPath;
	static std::string const k_spritePath;

	static int const k_playerMovementSpeed;
	static int const k_widthUnits;
	static int const k_heightUnits;
	static int const k_debounceFrames;

	static int const k_widthAdjustment;
	static int const k_heightAdjustment;

	static std::string const k_fontPath;
	static std::string const k_dialogDelimiter;
	static std::string const k_dialogEscape;
	static std::string const k_pictureExt;

	static char const k_dialogEscapeChar;
	static float const k_textFactor;

	static int const k_tileUnitSize;

	static std::string const k_tilemapPath;

	static int const k_tileMapUnitSizeInFile;

	static int const k_tileScreenWidthSize;
	static int const k_tileScreenHeightSize;


	static int const k_overlapBuffer;
};

#endif