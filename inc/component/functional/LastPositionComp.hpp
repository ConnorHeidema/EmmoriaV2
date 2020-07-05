#ifndef __LAST_POSITION_COMP__
#define __LAST_POSITION_COMP__

#include "util/Position.hpp"

/**
 * This component should be added to anything that needs to know its previous position
 */
struct LastPositionComp
{
	Position m_lastPosition;
};

#endif