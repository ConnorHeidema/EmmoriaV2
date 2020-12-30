#ifndef TEXTURE_CONTAINER_HPP
#define TEXTURE_CONTAINER_HPP

#include <unordered_map>
#include <memory>
#include <string>

namespace sf { class Texture; }

/**
 * The texture container acts as a way for objects to get the texture they need
 * without needing a new instance of the texture for every object
 */
class TextureContainer
{
public:
	TextureContainer();

	/**
	 * This will get the texture from a string name being the path for the texture. If it doesn't already exist, it
	 * will fetch the texture
	 * @param textureName The path and name of the texture file
	 * @return a shared pointer to the texture
	 */
	static std::shared_ptr<sf::Texture> GetTexture(std::string const& textureName);
private:
	/**
	 * This will load the texture if we don't currently have it.
	 * @param textureName the name of the texture
	 * @return The loaded texture
	 */
	static std::shared_ptr<sf::Texture> LoadTexture_(std::string const& textureName);

	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textureMap;
};

#endif
