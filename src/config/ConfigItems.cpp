#include "config/ConfigItems.hpp"

#include <iostream>
#include <fstream>
#include <string>

bool ConfigItems::LoadConfigFile(std::string configFilePath)
{
	std::string line;
	std::ifstream configFile("data/Config/config.ini");
  	if (configFile.is_open())
	{
		while (getline(configFile, line))
		{
			std::string key;
			bool value;
			if (line.find("=") == std::string::npos)
			{
				std::cout << "Malformed ini file" << std::endl;
			}
			else
			{
				int equalsPosition = line.find("=");
				key = line.substr(0, equalsPosition);
				value = line.substr(equalsPosition + 1) == "true" ? true : false;
				if (value)
					m_setConfigItems.insert(key);
			}
		}
		configFile.close();
	}
}

std::unordered_set<std::string> ConfigItems::m_setConfigItems = {};