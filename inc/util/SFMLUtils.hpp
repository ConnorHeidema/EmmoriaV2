#ifndef __SFML_UTILS__
#define __SFML_UTILS__

namespace sf { class Event; }

class SFMLUtils
{
public:
	static void ResetUserSFMLEventState();
	static bool ProcessSFMLEvents(sf::Event event);

	static int s_wheelMovement;
	static int testNum;
};

#endif