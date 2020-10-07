#ifndef __CLICKABLE_COMP__
#define __CLICKABLE_COMP__

/**
 * This component should be added to any entity which should be allowed to be clicked
 */
struct ClickableComp
{
	bool m_bLeftClicked;
	bool m_bRightClicked;
	int m_x;
	int m_y;

	ClickableComp()
		: m_bLeftClicked(false)
		, m_bRightClicked(false)
		, m_x(-1)
		, m_y(-1)
	{}
};

#endif