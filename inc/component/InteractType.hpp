#ifndef __INTERACTOR_TYPE__
#define __INTERACTOR_TYPE__
#include "entity/EntityMacro.hpp"
#define DEFINE_INTERACTOR_TYPES(name) name##_t ,
enum class InteractType_t { ALL_TAG_MACRO(DEFINE_INTERACTOR_TYPES) NUM_INTERACTOR_TYPE };
#include "entity/EntityMacroEnd.hpp"
#endif
