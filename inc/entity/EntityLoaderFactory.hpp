#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__

#include "entity/EntityMacro.hpp"

#include <entt/entt.hpp>

class EntityLoaderFactory
{
public:

	#define LOAD_DECL(name) \
		static void Load##name(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader);
	ALL_COMPONENT_PIECE_MACRO(LOAD_DECL)
	ALL_TAG_MACRO(LOAD_DECL)
	#undef LOAD_DEF
private:
	static std::string ReadString_(std::istringstream& reader);
};

#include "entity/EntityMacroEnd.hpp"

#endif