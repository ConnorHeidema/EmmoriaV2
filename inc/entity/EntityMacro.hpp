#define ENTITY_MACRO(macro, entity) \
	macro(entity)

#define ALL_COMPONENT_PIECE_MACRO(macroToUse) \
	macroToUse(Renderable) \
	macroToUse(Xposition) \
	macroToUse(Yposition) \
	macroToUse(Height) \
	macroToUse(Width) \
	macroToUse(Fullscreen) \
	macroToUse(Text) \
	macroToUse(Sprite)


#define ALL_TAG_MACRO(macroToUse) \
	macroToUse(ButtonComp) \
	macroToUse(DialogChainComp) \
	macroToUse(DialogChainFragmentComp) \
	macroToUse(PersistentComp) \
	macroToUse(PlayerComp) \
	macroToUse(RandomComp)

#define ALL_FUNCTIONAL_MACRO(macroToUse) \
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
	macroToUse(TextComp)
