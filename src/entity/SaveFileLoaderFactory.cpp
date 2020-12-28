#include "entity/SaveFileLoaderFactory.hpp"
#include "entity/EntityLoaderFactory.hpp"
#include "util/Entitymap.hpp"
#include "component/functional/LoadComp.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void SaveFileLoaderFactory::LoadFile(std::string const& nameOfFile, entt::registry& rReg)
{
	rReg.clear();
	auto entity = rReg.create();
	rReg.emplace<LoadComp>(entity).m_filePath = nameOfFile;
}
