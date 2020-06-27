#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__

#include "entity/EntityMacro.hpp"

#include <entt/entt.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

class EntityLoaderFactory
{
public:
	#define LOAD_DECL(name) \
		static void Load##name(entt::registry& reg, std::istringstream& reader);
	ALL_ENTITY_MACRO(LOAD_DECL)
	#undef LOAD_DEF
private:
	static int GetTextWidth_(std::string text, int height);
	static std::string ReadString_(std::istringstream& reader);
};

#include "entity/EntityMacroEnd.hpp"

#endif