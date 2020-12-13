#include <util/PortraitMapping.hpp>

uint32_t PortraitMapping::GetDialogIcon(std::string const& k_name)
{
	if (k_name == ":person:") return 1;
	if (k_name == ":sign:") return 2;
	return 0;
}
