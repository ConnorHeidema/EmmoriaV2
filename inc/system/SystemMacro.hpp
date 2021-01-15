#define STD_MAKE_UNIQUE_SYS(System) std::make_unique< System##Sys>( \
	std::string(#System) + \
	std::string("Sys"), \
	rReg),

#define STD_MAKE_UNIQUE_ANIMATION_SYS(System)	std::make_unique< System##Sys>( \
	std::string(#System) + \
	std::string("Sys"), \
	rReg, \
	rRenderWindow),

// ORDER IS THE SAME ORDER EACH SYSTEM WILL BE UPDATED EACH FRAME
#define DO_MACRO_FOR_ALL_SYSTEMS(m, m2) \
	m(Reboot)\
	m(Config)\
	m(Editor)\
	m(Reload)\
	m(Movement)\
	m(TileMap)\
	m(Loading)\
	m(Button)\
	m(Clickable)\
	m(Dialog)\
	m(Persistent)\
	m(Health)\
	m(SceneLoad)\
	m(Interacting)\
	m(Animation)\
	m2(GameRender)\
	m2(Light)\
	m2(MovieRender)\
	m(Blob)\
	m(Bow)\
	m(Sword)\
	m(Lifespan)\
	m(Door)\
	m(Switch)\
	m(Music)


#define DEFINE_SYSTEM_ENUM(name) name##_t,