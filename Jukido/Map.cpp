#include "Map.h"
#include "assert.h"

//#TODO, Bohdan: Make maps data-driven
const Map::TilesMapType Map::R_AND_D_MAP =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,0,1,1,1,1,0,0,0,0,1,0,0,0,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const Map::TilesMapType Map::PACMAN_MAP1 =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1},
	{1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1},
	{1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
	{1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const Map::TilesMapType Map::PACMAN_MAP2 =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1},
	{1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,0,1,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const Map::TilesMapType Map::FLAT =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Map::Map()
{
	createTileShapes();
}

bool Map::isTileBlocked(const sf::Vector2f& position) const
{
	const int x = static_cast<int>(position.x / TILE_WIDTH);
	const int y = static_cast<int>(position.y / TILE_HEIGHT);

	if (x >= m_tilesMap[0].size() || x < 0)
	{
		//assert(false && "Invalid x was passed for the map Check");
		return true;
	}

	if (y >= m_tilesMap.size() || y < 0)
	{
		//assert(false && "Invalid x was passed for the map Check");
		return true;
	}

	return m_tilesMap[y][x];
}

bool Map::isPositionInTile(const sf::Vector2f& position, const sf::Vector2u& tile) const
{
	const int x = static_cast<int>(position.x / TILE_WIDTH);
	const int y = static_cast<int>(position.y / TILE_HEIGHT);

	return (x == tile.x && y == tile.y);
}

sf::Vector2f Map::getRandomValidPosition() const
{
	//#TODO, General: Make it more efficient
	while (true)
	{
		const int x = rand() % m_tilesMap[0].size();
		const int y = rand() % m_tilesMap.size();

		if (!m_tilesMap[y][x])
		{
			return { x * TILE_WIDTH + TILE_WIDTH / 2, y * TILE_HEIGHT + TILE_HEIGHT / 2 };
		}
	}

	return {};
}

sf::Vector2f Map::getPositionFromTile(const sf::Vector2u& tile) const
{
	return sf::Vector2f(tile.x * TILE_WIDTH + TILE_WIDTH / 2, tile.y * TILE_HEIGHT + TILE_HEIGHT / 2);
}

sf::Vector2u Map::getTileFromPosition(const sf::Vector2f& gameObjectPosition) const
{
	const int x = static_cast<int>(gameObjectPosition.x / TILE_WIDTH);
	const int y = static_cast<int>(gameObjectPosition.y / TILE_HEIGHT);

	if (x >= m_tilesMap[0].size() || x < 0)
	{
		assert(false && "Invalid x was passed for the map Check");
		return { 0, 0 };
	}

	if (y >= m_tilesMap.size() || y < 0)
	{
		assert(false && "Invalid x was passed for the map Check");
		return { 0, 0 };
	}

	return sf::Vector2u{ static_cast<unsigned>(x), static_cast<unsigned>(y) };
}

void Map::draw(sf::RenderWindow* window)
{
	for (auto& tileShape : m_tilesShapes)
	{
		window->draw(tileShape);
	}
}

void Map::createTileShapes()
{
	const sf::Vector2u windowSize = WindowHelper::Instance().GetRenderWindow().getSize();
	TILE_WIDTH = windowSize.x / m_tilesMap[0].size(); //#TODO, General: VALIDATE SIZES
	TILE_HEIGHT = windowSize.y / m_tilesMap.size();

	int x = 0;
	int y = 0;
	m_tilesShapes.reserve(m_tilesMap[0].size() * m_tilesMap.size());

	for (auto& row : m_tilesMap)
	{
		x = 0;
		for (auto tile : row)
		{
			sf::RectangleShape tileShape = sf::RectangleShape({ TILE_WIDTH, TILE_HEIGHT });

			tileShape.setPosition(x, y);
			tileShape.setFillColor(tile ? sf::Color::Red : sf::Color::Green);

			m_tilesShapes.push_back(std::move(tileShape));
			x += TILE_WIDTH;
		}
		y += TILE_HEIGHT;
	}
}