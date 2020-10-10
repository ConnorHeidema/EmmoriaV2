#ifndef __ENTT_UTILS__
#define __ENTT_UTILS__

#include "entt/entt.hpp"

#include <unordered_map>
#include <string>

template <typename T>
class EnttUtils
{
public:
    static bool ComponentExists(entt::registry& rReg);
};

template <typename T>
bool EnttUtils<T>::ComponentExists(entt::registry& rReg)
{
	bool bExists = false;
	rReg.view<T>().each([&](auto entity) { bExists = true; });
	return bExists;
}

#endif