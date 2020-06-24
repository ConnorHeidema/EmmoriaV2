#include "util/Helper.hpp"

#include <stdlib.h>
#include <time.h>

int Helper::Rand(int const& lowerBound, int const& higherBound)
{
	srand(time(NULL));
	return rand() % higherBound + lowerBound;
}