#include <iostream>
#include <tileset.h>

void Tileset::update(sf::Int32 deltaMS)
{
	for (Tile* tile : m_tileSet)
	{
		tile->update(deltaMS);
	}
}

void Tileset::render(sf::RenderWindow& window)
{
	for (Tile* tile : m_tileSet)
	{
		tile->render(window);
	}
}

void Tileset::init(int numberToInstantiate)
{
	// Instanciar el máximo necesario (por ejemplo, si la dificultad dificil es 10x10, instanciar 100 y luego usar esas durante el resto de la partida, activando y desactivandolas
	for (int i = 0; i < numberToInstantiate; i++)
	{
		m_tileSet.push_back(new Tile());
	}

	for (Tile* tile : m_tileSet)
	{
		tile->init();
	}

	m_allInstantiatedTiles = numberToInstantiate;
}

void Tileset::instantiate(int rows, int columns)
{
	m_tileArray.resize(rows, std::vector<Tile*>(columns, nullptr)); // Resize the matrix to make it of size (rows, columns)

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			m_tileArray[i][j] = new Tile(); // Create a tile for each position
		}
	}
}

void Tileset::activate(int posX, int posY)
{
	std::cout << "Attempting to spawn a tile in pos (" << posX << "," << posY << ")...\n";
	int i = 0;

	for (const Tile* tile : m_tileSet)
	{
		if (!tile->getActive())
		{
			std::cout << "Inactive tile found\n";
			m_tileSet[i]->activate(posX, posY);
			return;
		}
		i++;
	}

	int j = 0;

	std::cout << "Inactive tile not found...\n";
	std::cout << "Instantiating new tile...";

	m_tileSet.push_back(new Tile());
	m_allInstantiatedTiles++;
	m_tileSet[m_allInstantiatedTiles - 1]->activate(posX, posY);
}

void Tileset::restart()
{
	for (Tile* tile : m_tileSet)
	{
		tile->restart();
	}
}
