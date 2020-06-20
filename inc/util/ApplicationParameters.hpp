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
};

#endif