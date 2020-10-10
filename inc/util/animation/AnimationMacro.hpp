#define ANIMATION_MACRO(macro, animation) \
	macro(animation)

#define ALL_ANIMATION_MACRO(macroToUse) \
	macroToUse(DawnPillar) \
	macroToUse(Blob) \
	macroToUse(Player) \
	macroToUse(Depressable) \
	macroToUse(DoorLooking)

#define ALL_TILEMAP_ANIMATION_MACRO(macroToUse) \
	macroToUse(DawnPillar)

#define ALL_COMP_ANIMATION_MACRO(macroToUse) \
	macroToUse(Blob) \
	macroToUse(Player) \
	macroToUse(Depressable) \
	macroToUse(DoorLooking)
