#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__


#include <entt/entt.hpp>

class EntityLoaderFactory
{
public:

	#include "entity/EntityMacro.hpp"
	#define LOAD_DECL(name) \
		static void Load##name(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader);
	ALL_TAG_MACRO(LOAD_DECL)
	ALL_FUNCTIONAL_MACRO(LOAD_DECL)
	ALL_COMPONENT_PIECE_MACRO(LOAD_DECL)
	#undef LOAD_DEF
	#include "entity/EntityMacroEnd.hpp"
};


#endif