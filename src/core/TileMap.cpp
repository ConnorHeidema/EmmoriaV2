#include "core/TileMap.hpp"

#include "util/ApplicationParameters.hpp"

int const TileMap::m_kQuadVertices = 4;

TileMap::TileMap()
	: m_fileToUse("")
{
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize((
		ApplicationParameters::k_widthUnits *
		ApplicationParameters::k_heightUnits) /
		ApplicationParameters::k_tileUnitSize /
		ApplicationParameters::k_tileUnitSize *
		TileMap::m_kQuadVertices);
}

void TileMap::PopulateQuad(
	int const& xPosition,
	int const& yPosition,
	int const& fileTileIndex)
{
	int tileNumber = GetCurrentTileNumber_(xPosition, yPosition);

	sf::Vertex* currentTile = &m_vertices[tileNumber * TileMap::m_kQuadVertices];

	DefineQuadCorners_(currentTile, xPosition, yPosition);
	ApplyTexturesToCorners_(currentTile, fileTileIndex);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}

int TileMap::GetCurrentTileNumber_(
	int const& xPosition,
	int const& yPosition)
{
	int xIndex = (xPosition - ApplicationParameters::k_tileScreenWidthSize / 2) / ApplicationParameters::k_tileScreenWidthSize;
	int yIndex = (yPosition - ApplicationParameters::k_tileScreenHeightSize / 2) / ApplicationParameters::k_tileScreenHeightSize;
	return xIndex + yIndex * ApplicationParameters::k_widthUnits / ApplicationParameters::k_tileUnitSize;
}

void TileMap::DefineQuadCorners_(
	sf::Vertex* currentTile,
	int const& xPosition,
	int const& yPosition)
{
	currentTile[TOP_LEFT].position =
		sf::Vector2f(
			xPosition - ApplicationParameters::k_fTileScreenWidthSize / 2,
			yPosition - ApplicationParameters::k_fTileScreenHeightSize / 2);

	currentTile[TOP_RIGHT].position =
		sf::Vector2f(
			xPosition + ApplicationParameters::k_fTileScreenWidthSize / 2,
			yPosition - ApplicationParameters::k_fTileScreenHeightSize / 2);

	currentTile[BOTTOM_RIGHT].position =
		sf::Vector2f(
			xPosition + ApplicationParameters::k_fTileScreenWidthSize / 2,
			yPosition + ApplicationParameters::k_fTileScreenHeightSize / 2);

	currentTile[BOTTOM_LEFT].position =
		sf::Vector2f(
			xPosition - ApplicationParameters::k_fTileScreenWidthSize / 2,
			yPosition + ApplicationParameters::k_fTileScreenHeightSize / 2);
}

void TileMap::ApplyTexturesToCorners_(
	sf::Vertex* currentTile,
	int const& textureColumn)
{
	currentTile[TOP_LEFT].texCoords = sf::Vector2f(
		float(ApplicationParameters::k_tileMapUnitSizeInFile*textureColumn),
		0);

	currentTile[TOP_RIGHT].texCoords = sf::Vector2f(
		float(ApplicationParameters::k_tileMapUnitSizeInFile*(textureColumn + 1)),
		0);

	currentTile[BOTTOM_RIGHT].texCoords = sf::Vector2f(
		float(ApplicationParameters::k_tileMapUnitSizeInFile*(textureColumn + 1)),
		float(ApplicationParameters::k_tileMapUnitSizeInFile));

	currentTile[BOTTOM_LEFT].texCoords = sf::Vector2f(
		float(ApplicationParameters::k_tileMapUnitSizeInFile*textureColumn),
		float(ApplicationParameters::k_tileMapUnitSizeInFile));
}
