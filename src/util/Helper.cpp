#include "util/Helper.hpp"

#include <stdlib.h>

Helper::Helper()
{

}

bool Helper::m_firstInitialization = false;

int Helper::Rand(int const& lowerBound, int const& higherBound)
{
	if (!m_firstInitialization)
	{
		srand(time(0));
		m_firstInitialization = true;
	}
	return rand() % ((higherBound + 1) - lowerBound) + lowerBound;
}
