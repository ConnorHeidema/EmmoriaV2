#include "util/EntityLoaderUtils.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/FontContainer.hpp"

#include <SFML/Graphics/Text.hpp>

int EntityLoaderUtils::GetTextWidth(std::string text, int height)
{
	sf::Text dummyText;
	sf::Font font;
	font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
	dummyText.setFont(font);
	dummyText.setCharacterSize(static_cast<unsigned int>(height*ApplicationParameters::k_textFactor));
	dummyText.setString(text);
	return static_cast<int>(dummyText.getLocalBounds().width);
}