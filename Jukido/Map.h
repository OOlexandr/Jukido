#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "WindowHelper.h"

//#TODO, Bohdan: Make it GameObject as well with a set
//of Tiles as other GameObjects
//Either blockable or not

class Map
{
public:
	static Map& GetInstance()
	{
		static Map map;
		return map;
	}

	Map();

	bool isTileBlocked(const sf::Vector2f& position) const;
	bool isPositionInTile(const sf::Vector2f& position, const sf::Vector2u& tile) const;
	sf::Vector2f getRandomValidPosition() const;

	sf::Vector2f getPositionFromTile(const sf::Vector2u& tile) const;
	sf::Vector2u getTileFromPosition(const sf::Vector2f& position) const;

	//TODO: Bohdan, shouldn't be here, create MapRenderer Object
	void draw(sf::RenderWindow* window);

	using TilesMapType = std::vector<std::vector<bool >>;

	const TilesMapType& getAllTiles() const { return m_tilesMap; }
	sf::Vector2u GetMapSize() const { return { static_cast<unsigned>(m_tilesMap[0].size()), static_cast<unsigned>(m_tilesMap.size()) }; }

private:
	float TILE_WIDTH = 200.0f;
	float TILE_HEIGHT = 200.0f;

private:

	TilesMapType m_tilesMap = FLAT;

	static const TilesMapType R_AND_D_MAP;
	static const TilesMapType PACMAN_MAP1;
	static const TilesMapType PACMAN_MAP2;
	static const TilesMapType FLAT;

	std::vector<sf::RectangleShape> m_tilesShapes;
	void createTileShapes();
};
