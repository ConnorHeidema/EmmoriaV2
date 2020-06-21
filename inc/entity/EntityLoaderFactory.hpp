#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__

#include <entt/entt.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

class EntityLoaderFactory
{
public:
	#define LOAD_DECL(name) \
		static void Load##name(entt::registry& reg, std::istringstream& reader);

		LOAD_DECL(File)
		LOAD_DECL(Background)
		LOAD_DECL(Dialog)
	#undef LOAD_DEF
};
#endif