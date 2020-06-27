#ifndef __CLICKABLE_COMP__
#define __CLICKABLE_COMP__

/**
 * This component should be added to any entity which should be allowed to be clicked
 */
struct ClickableComp
{
	// When the frame wait counters are 1, the object has technically been clicked.
	bool leftClicked;
	bool rightClicked;
	int scrollWheelValue;
};

#endif