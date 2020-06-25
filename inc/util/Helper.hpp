#ifndef __HELPER__
#define __HELPER__

#include "util/Mediamap.hpp"
#include "util/Entitymap.hpp"

#include <unordered_map>
#include <string>
#include <experimental/filesystem>

class Helper
{
public:
	Helper();
	static int Rand(int const& lowest, int const& highest);
};

class HelperHelper
{
private:
	static Helper m_helper;
};

#endif