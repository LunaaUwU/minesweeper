#include <iostream>
#include <tileset.h>

void Tileset::update(sf::Int32 deltaMS)
{
	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->update(deltaMS);
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_canClickHorizontal)
		{
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // De-select
			if (m_selectedTileY == m_columns - 1)
			{
				m_selectedTileY = 0;
			}
			else
			{
				m_selectedTileY++;
			}
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // Select
			m_canClickHorizontal = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_canClickHorizontal)
		{
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // De-select
			if (m_selectedTileY == 0)
			{
				m_selectedTileY = m_columns - 1;
			}
			else
			{
				m_selectedTileY--;
			}
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // Select
			m_canClickHorizontal = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_canClickVertical)
		{
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // De-select
			if (m_selectedTileX == m_rows - 1)
			{
				m_selectedTileX = 0;
			}
			else
			{
				m_selectedTileX++;
			}
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // Select
			m_canClickVertical = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_canClickVertical)
		{
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // De-select
			if (m_selectedTileX == 0)
			{
				m_selectedTileX = m_rows - 1;
			}
			else
			{
				m_selectedTileX--;
			}
			m_tileArray[m_selectedTileX][m_selectedTileY]->select(); // Select
			m_canClickVertical = false;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_canClickHorizontal = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_canClickVertical = true;
	}
}

void Tileset::render(sf::RenderWindow& window)
{
	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->render(window);
		}
	}
}

void Tileset::init(int rows, int columns)
{
	m_tileArray.resize(rows, std::vector<Tile*>(columns, nullptr)); // Resize the matrix to make it of size (rows, columns)

	m_rows = rows;
	m_columns = columns;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			m_tileArray[i][j] = new Tile(); // Create a tile for each position
			m_tileArray[i][j]->init();
		}
	}

	m_allInstantiatedTiles = rows * columns;
}

void Tileset::instantiate()
{
	
}

void Tileset::activate(int posX, int posY)
{
	std::cout << "Attempting to spawn a tile in pos (" << posX << "," << posY << ")...\n";

	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			if (!tile->getActive())
			{
				std::cout << "Inactive tile found\n";
				tile->activate(posX, posY);
				return;
			}
		}
	}

	std::cout << "Inactive tile not found\n";
}

void Tileset::restart()
{
	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->restart();
		}
	}
}
