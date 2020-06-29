#define ENTITY_MACRO(macro, entity) \
	macro(entity)

#define ALL_ENTITY_MACRO(macroToUse) \
	macroToUse(File) \
	macroToUse(Background) \
	macroToUse(RandomDialog) \
	macroToUse(Player)
