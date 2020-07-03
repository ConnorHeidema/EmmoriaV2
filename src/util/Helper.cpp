#include "util/Helper.hpp"

#include <stdlib.h>
#include <time.h>

Helper::Helper()
{
	srand(time(NULL));
}

int Helper::Rand(int const& lowerBound, int const& higherBound)
{
	return rand() % ((higherBound + 1) - lowerBound) + lowerBound;
}
