#include "loader/EntityLoader.hpp"
#include "util/ApplicationParameters.hpp"

EntityLoader::EntityLoader()
{}

void EntityLoader::LoadEntities(entt::registry& reg, std::string filename)
{
	std::string token;
	std::ifstream file(ApplicationParameters::k_dataPath + filename);
	while(std::getline(file, token)) {
		std::istringstream line(token);
		line >> token;
		Entitymap::m_entityMap.at(token)(reg, line);
	}
}
