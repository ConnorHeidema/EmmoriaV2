#ifndef __HELPER__
#define __HELPER__

#include "util/Mediamap.hpp"
#include "util/Entitymap.hpp"

#include <unordered_map>
#include <string>

class Helper
{
public:
	Helper();
	static int Rand(int const& lowest, int const& highest);
	static int Mod(int a, int b);
	static bool m_firstInitialization;
};

#endif