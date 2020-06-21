#include "util/ApplicationParameters.hpp"

#include <SFML/Graphics.hpp>

int const ApplicationParameters::k_screenWidth = sf::VideoMode::getDesktopMode().width;
int const ApplicationParameters::k_screenHeight = sf::VideoMode::getDesktopMode().height;
int const ApplicationParameters::k_framerate = 60;
std::string const ApplicationParameters::k_windowName = "Emmoria";
std::string const ApplicationParameters::k_dataPath = "data/";
std::string const ApplicationParameters::k_spritePath = "sprite/";
int const ApplicationParameters::k_playerMovementSpeed = 3;
int const ApplicationParameters::k_widthUnits = 100;
int const ApplicationParameters::k_heightUnits = 100;
