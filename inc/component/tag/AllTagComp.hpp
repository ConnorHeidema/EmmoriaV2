#ifndef __ALL_TAG_COMP__
#define __ALL_TAG_COMP__
#include "entity/EntityMacro.hpp"

#define DEFINE_INTERACTOR_TYPES(name) name##_t ,
enum class InteractorType_t { ALL_TAG_MACRO(DEFINE_INTERACTOR_TYPES) ALL_INTERACTOR_TYPES };
#define DEFINE_TAG_STRUCTS(name) struct name { };
ALL_TAG_MACRO(DEFINE_TAG_STRUCTS)
#include "entity/EntityMacroEnd.hpp"
#endif
