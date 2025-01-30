#include <iostream>
#include <tileset.h>

void Tileset::update(sf::Int32 deltaMS)
{
	for (std::vector<Tile*> row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->update(deltaMS);
		}
	}
}

void Tileset::render(sf::RenderWindow& window)
{
	for (std::vector<Tile*> row : m_tileArray)
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

	for (std::vector<Tile*> row : m_tileArray)
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
	for (std::vector<Tile*> row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->restart();
		}
	}
}
