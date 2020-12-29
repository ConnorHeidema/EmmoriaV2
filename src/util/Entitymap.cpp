#include "util/Entitymap.hpp"

#include "entity/EntityLoaderFactory.hpp"

std::unordered_map<std::string, fnEntityfactory> Entitymap::Create_map()
{
	std::unordered_map<std::string, fnEntityfactory> m;

	#include "entity/EntityMacro.hpp"
	#define LOADER_TYPE(name) m[#name] = EntityLoaderFactory::Load##name;
	ALL_TAG_MACRO(LOADER_TYPE)
	ALL_FUNCTIONAL_MACRO(LOADER_TYPE)
	ALL_COMPONENT_PIECE_MACRO(LOADER_TYPE)
	#undef LOADER_TYPE
	#include "entity/EntityMacroEnd.hpp"

	return m;
}

std::unordered_map<std::string, fnEntityfactory> const Entitymap::m_entityMap =  Entitymap::Create_map();
