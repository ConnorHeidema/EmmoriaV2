#define ENTITY_MACRO(macro, entity) \
	macro(entity)

#define ALL_TAG_MACRO(macroToUse) \
	macroToUse(DialogChainComp) \
	macroToUse(DialogChainFragmentComp) \
	macroToUse(HealingPadComp) \
	macroToUse(PersistentComp) \
	macroToUse(PlayerComp) \
	macroToUse(RandomComp) \
	macroToUse(WallComp)

#define ALL_FUNCTIONAL_MACRO(macroToUse) \
	macroToUse(ButtonComp) \
	macroToUse(ClickableComp) \
	macroToUse(HealthComp) \
	macroToUse(InteractableComp) \
	macroToUse(InteractorComp) \
	macroToUse(LastPositionComp) \
	macroToUse(LoadComp) \
	macroToUse(MovieComp) \
	macroToUse(PositionComp) \
	macroToUse(RenderableComp) \
	macroToUse(SizeComp) \
	macroToUse(SpriteComp) \
	macroToUse(TextComp) \
	macroToUse(TileMapComp) \
	macroToUse(TileMapPieceComp)

#define ALL_COMPONENT_PIECE_MACRO(macroToUse) \
	macroToUse(Xposition) \
	macroToUse(Yposition) \
	macroToUse(Height) \
	macroToUse(Width) \
	macroToUse(Fullscreen) \
	macroToUse(Button) \
	macroToUse(RandomDialog) \
	macroToUse(IndexedPosition) \
	macroToUse(WallTile)
