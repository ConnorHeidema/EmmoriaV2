#include "util/Helper.hpp"

#include <stdlib.h>
#include <ctime>

Helper::Helper()
{

}

bool Helper::m_firstInitialization = false;

int Helper::Rand(int const& lowerBound, int const& higherBound)
{
	if (!m_firstInitialization)
	{
		srand(static_cast<unsigned int>(time(0)));
		m_firstInitialization = true;
	}
	return rand() % ((higherBound + 1) - lowerBound) + lowerBound;
}

int Helper::Mod(int a, int b) { return (a % b + b) % b; }