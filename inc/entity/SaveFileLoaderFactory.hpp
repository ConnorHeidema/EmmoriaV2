#ifndef __SAVEFILE_LOADER_FACTORY__
#define __SAVEFILE_LOADER_FACTORY__


#include <entt/entt.hpp>

class SaveFileLoaderFactory
{
public:
	static void LoadFile(std::string const&,entt::registry&);
};


#endif