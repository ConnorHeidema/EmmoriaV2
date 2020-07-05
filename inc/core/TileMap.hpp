#ifndef __TILE_MAP__
#define __TILE_MAP__

#include <SFML/Graphics.hpp>

enum Corners_t
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT
};

class TileMap
	: public sf::Drawable
	, public sf::Transformable
{
public:
	TileMap();

	void PopulateQuad(
		int const& xPosition,
		int const& yPosition,
		int const& fileTileIndex);

	std::string m_fileToUse;
    sf::Texture m_tileset;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	int GetCurrentTileNumber_(
		int const& xPosition,
		int const& yPosition);

	void DefineQuadCorners_(
		sf::Vertex* currentTile,
		int const& xPosition,
		int const& yPosition);

	void ApplyTexturesToCorners_(
		sf::Vertex* currentTile,
		int const& textureColumn);

	sf::VertexArray m_vertices;
	static int const m_kQuadVertices;
};

#endif