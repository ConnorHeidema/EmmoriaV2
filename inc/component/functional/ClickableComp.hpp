#ifndef __CLICKABLE_COMP__
#define __CLICKABLE_COMP__

/**
 * This component should be added to any entity which should be allowed to be clicked
 */
struct ClickableComp
{
	bool m_bLeftClicked;
	bool m_bRightClicked;
};

#endif