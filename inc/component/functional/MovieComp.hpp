#ifndef __MOVIE_COMP__
#define __MOVIE_COMP__

#include "util/Mediamap.hpp"

/**
 * This component should be added and changed
 * when the current media is changed
 */
struct MovieComp
{
	Media_t m_currentMedia;
	MovieComp()
		: m_currentMedia(Media_t::NONE)
	{}
};

#endif