#ifndef __RENDERABLE_COMP__
#define __RENDERABLE_COMP__

/**
 * This component should be added to anything that is renderable
 */
struct RenderableComp
{
	bool m_bRendered;
	RenderableComp()
		: m_bRendered(false)
	{}
};

#endif