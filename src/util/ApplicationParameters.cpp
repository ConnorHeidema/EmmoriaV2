#include "util/ApplicationParameters.hpp"

#include <SFML/Graphics.hpp>

int const ApplicationParameters::k_screenWidth = sf::VideoMode::getDesktopMode().width;
int const ApplicationParameters::k_screenHeight = sf::VideoMode::getDesktopMode().height;
int const ApplicationParameters::k_framerate = 60;

std::string const ApplicationParameters::k_windowName = "Emmoria";
std::string const ApplicationParameters::k_dataPath = "data/";
std::string const ApplicationParameters::k_spritePath = "sprite/";

int const ApplicationParameters::k_widthUnits = 120;
int const ApplicationParameters::k_heightUnits = 108;
int const ApplicationParameters::k_debounceFrames = 10;

int const ApplicationParameters::k_widthAdjustment = ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
int const ApplicationParameters::k_heightAdjustment = ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

std::string const ApplicationParameters::k_fontPath = "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"; // should be more generic in the future.
std::string const ApplicationParameters::k_dialogDelimiter = "-";
std::string const ApplicationParameters::k_dialogEscape = "*";
std::string const ApplicationParameters::k_pictureExt = ".png";

char const ApplicationParameters::k_dialogEscapeChar = '*';
float const ApplicationParameters::k_textFactor = 0.75f;

int const ApplicationParameters::k_tileUnitSize = 6;

std::string const ApplicationParameters::k_tilemapPath = "sprite/tilemap/";

int const ApplicationParameters::k_tileMapUnitSizeInFile = 100;

int const ApplicationParameters::k_tileScreenWidthSize = ApplicationParameters::k_widthAdjustment * ApplicationParameters::k_tileUnitSize;

int const ApplicationParameters::k_tileScreenHeightSize = ApplicationParameters::k_heightAdjustment * ApplicationParameters::k_tileUnitSize;

int const ApplicationParameters::k_overlapBuffer = 4;

int const ApplicationParameters::k_widthTiles = 20;
int const ApplicationParameters::k_heightTiles = 15;

int const ApplicationParameters::k_bottomOfScreen = k_heightTiles * k_tileScreenHeightSize;
int const ApplicationParameters::k_rightOfScreen = k_widthTiles * k_tileScreenWidthSize;

uint64_t ApplicationParameters::uCurrentDialogIndex = 0;