#ifndef __CONFIG_ITEMS__
#define __CONFIG_ITEMS__

#include <unordered_set>

/**
 * This class is responsible for providing access to any config items that should
 * be loaded the the start from an ini file
 */
class ConfigItems
{
public:
	static bool LoadConfigFile(std::string const& configFilePath);
	static std::unordered_set<std::string> m_setConfigItems;
private:
	static std::unordered_set<std::string> m_currentSetConfigItems;
	ConfigItems();
};

#endif