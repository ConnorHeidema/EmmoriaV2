#ifndef __DIALOG_COMP__
#define __DIALOG_COMP__

#include <string>

/**
 * This component should be added for any dialog which should be shown on screen
 */
struct DialogComp
{
	uint64_t uCurrentDialogIndex;
	uint32_t uSpriteIndex;
	std::string content;
	std::string fileToLoadAfter;
};

#endif
