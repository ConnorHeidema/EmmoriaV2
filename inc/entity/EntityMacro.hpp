#define ENTITY_MACRO(macro, entity) \
	macro(entity)

#define ALL_TAG_MACRO(macroToUse) \
	macroToUse(DialogChainComp) \
	macroToUse(DialogChainFragmentComp) \
	macroToUse(HealingPadComp) \
	macroToUse(PersistentComp) \
	macroToUse(PlayerComp) \
	macroToUse(RandomComp) \
	macroToUse(WallComp) \
	macroToUse(DeloadableComp) \
	macroToUse(BowComp) \
	macroToUse(ItemActionAreaComp) \
	macroToUse(ArrowComp) \
	macroToUse(WallInteractorComp) \
	macroToUse(DeleteAfterInteractionComp) \
	macroToUse(RebootComp) \
	macroToUse(AnimationRebootComp) \
	macroToUse(BlobComp) \
	macroToUse(HoleComp) \
	macroToUse(WeightComp) \
	macroToUse(DepressableComp) \
	macroToUse(DoorLookingComp) \
	macroToUse(SignComp) \
	macroToUse(NearbyPlayerComp) \
	macroToUse(StructuredDialogComp)


#define ALL_FUNCTIONAL_MACRO(macroToUse) \
	macroToUse(ButtonComp) \
	macroToUse(ClickableComp) \
	macroToUse(DialogComp) \
	macroToUse(DialogFacadeComp) \
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
	macroToUse(TileMapPieceComp) \
	macroToUse(LocationComp) \
	macroToUse(RotationComp) \
	macroToUse(SpeedComp) \
	macroToUse(TrackingComp) \
	macroToUse(SwitchComp) \
	macroToUse(DoorComp) \
	macroToUse(MaxHealthComp) \
	macroToUse(SignInfoComp)

#define ALL_COMPONENT_PIECE_MACRO(macroToUse) \
	macroToUse(Xposition) \
	macroToUse(Yposition) \
	macroToUse(Height) \
	macroToUse(Width) \
	macroToUse(Fullscreen) \
	macroToUse(Button) \
	macroToUse(RandomDialog) \
	macroToUse(BottomDialog) \
	macroToUse(IndexedPosition) \
	macroToUse(WallTile) \
	macroToUse(Blob) \
	macroToUse(HoleTile)
