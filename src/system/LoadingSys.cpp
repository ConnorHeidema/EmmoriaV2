#include "system/LoadingSys.hpp"

#include "component/LoadComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/Entitymap.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

void LoadingSys::Update(entt::registry& reg)
{
	reg.view<LoadComp>().each([&](auto entity, auto &loadComp) {
		std::string token;
		std::ifstream file(ApplicationParameters::k_dataPath + loadComp.filePath);
		std::cout << ApplicationParameters::k_dataPath + loadComp.filePath;
		while(std::getline(file, token))
		{
			std::istringstream line(token);
			line >> token;
			std::cout << ApplicationParameters::k_dataPath + loadComp.filePath;
			Entitymap::m_entityMap.at(token)(reg, line);
		}
		reg.remove_all(entity);
	});
}
