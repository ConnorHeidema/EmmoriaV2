#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__

#include "entity/EntityMacro.hpp"

#include <entt/entt.hpp>

class EntityLoaderFactory
{
public:
	#define LOAD_DECL(name) \
		static void Load##name(entt::registry& reg, std::istringstream& reader);
	ALL_ENTITY_MACRO(LOAD_DECL)
	#undef LOAD_DEF
private:
	static std::string ReadString_(std::istringstream& reader);
};

#include "entity/EntityMacroEnd.hpp"

#endif