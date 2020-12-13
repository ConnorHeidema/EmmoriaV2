#ifndef __PORTRAIT_MAPPING__
#define __PORTRAIT_MAPPING__

#include <cstdint>
#include <string>

class PortraitMapping
{
public:
	static uint32_t GetDialogIcon(std::string const& name);
};

#endif