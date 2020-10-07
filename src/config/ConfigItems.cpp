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
				std::cout << "Malformed ini file: no equals character" << std::endl;
			}
			else
			{
				int equalsPosition = line.find("=");
				key = line.substr(0, equalsPosition);
				std::string stringValue = line.substr(equalsPosition + 1);
				if (!(stringValue == "true" || stringValue == "false"))
				{
					std::cout << "Malformed ini file: value not true or false" << std::endl;
				}
				value = stringValue == "true" ? true : false;
				if (value)
					m_setConfigItems.insert(key);
			}
		}
		configFile.close();
	}
	return true;
}

std::unordered_set<std::string> ConfigItems::m_setConfigItems = {};