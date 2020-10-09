#ifndef __LIFESPAN_COMP__
#define __LIFESPAN_COMP__

#include "util/Position.hpp"

/**
 * This component will kill an entity after n cycles
 */
struct LifespanComp
{
	int m_framesToLive;
};

#endif