#define ENTITY_MACRO(macro, entity) \
	macro(entity)

#define ALL_TAG_MACRO(macroToUse) \
	macroToUse(DialogChainComp) \
	macroToUse(DialogChainFragmentComp) \
	macroToUse(PersistentComp) \
	macroToUse(PlayerComp) \
	macroToUse(RandomComp)

#define ALL_FUNCTIONAL_MACRO(macroToUse) \
	macroToUse(ButtonComp) \
	macroToUse(ClickableComp) \
	macroToUse(HealthComp) \
	macroToUse(InteractableComp) \
	macroToUse(InteractorComp) \
	macroToUse(LoadComp) \
	macroToUse(MovieComp) \
	macroToUse(PositionComp) \
	macroToUse(RenderableComp) \
	macroToUse(SizeComp) \
	macroToUse(SpriteComp) \
	macroToUse(TextComp) \
	macroToUse(TileMapComp)

#define ALL_COMPONENT_PIECE_MACRO(macroToUse) \
	macroToUse(Xposition) \
	macroToUse(Yposition) \
	macroToUse(Height) \
	macroToUse(Width) \
	macroToUse(Fullscreen) \
	macroToUse(Button) \
	macroToUse(RandomDialog)
