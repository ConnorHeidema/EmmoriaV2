#ifndef FONT_CONTAINER_HPP
#define FONT_CONTAINER_HPP

#include <unordered_map>
#include <memory>
#include <string>

namespace sf { class Font; }

/**
 * The font container acts as a way for objects to get the font they need
 * without needing a new instance of the font for every object
 */
class FontContainer
{
public:
	FontContainer();

	/**
	 * This will get the font from a string name being the path for the font. If it doesn't already exist, it
	 * will fetch the font
	 * @param fontName The path and name of the font file
	 * @return a shared pointer to the font
	 */
	static std::shared_ptr<sf::Font> GetFont(std::string const& fontName);
private:
	/**
	 * This will load the font if we don't currently have it.
	 * @param fontName the name of the font
	 * @return The loaded font
	 */
	static std::shared_ptr<sf::Font> LoadFont_(std::string const& fontName);

	static std::unordered_map<std::string, std::shared_ptr<sf::Font>> m_fontMap;
};

#endif
