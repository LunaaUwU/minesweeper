#include <iostream>
#include <tileset.h>

#include <random>

void Tileset::update(sf::Int32 deltaMS)
{
	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->update(deltaMS);
		}
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !m_tileArray[m_selectedTileX][m_selectedTileY]->getIsFlagged() && m_canClick && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		m_tileArray[m_selectedTileX][m_selectedTileY]->openTile();
		if (m_isFirstTile)
		{
			fillBombs();
			// TODO set tile values
			m_isFirstTile = false;
		}
		m_canClick = false;
		// If tile is 0, open the ones around, and if its bomb, then bobm
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen() && m_canClick && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_tileArray[m_selectedTileX][m_selectedTileY]->flagTile();
		m_canClick = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_canClick = true;
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

void Tileset::init(int rows, int columns, int numberOfBombs)
{
	m_tileArray.resize(rows, std::vector<Tile*>(columns, nullptr)); // Resize the matrix to make it of size (rows, columns)

	m_rows = rows;
	m_columns = columns;
	m_numberOfBombs = numberOfBombs;
	m_bombsLeft = numberOfBombs;

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


void Tileset::fillBombs()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribX(0, m_columns - 1);
	std::uniform_int_distribution<int> distribY(0, m_rows - 1);
	int randomX = 0;
	int randomY = 0;
	while (m_bombsLeft > 0)
	{
		randomX = distribX(gen);
		randomY = distribY(gen);

		std::cout << "Selected tile is: (" << m_selectedTileX << "," << m_selectedTileY << ")\n";
		std::cout << "Random X between (0," << m_columns - 1 << ") = " << randomX << "\n";
		std::cout << "Random Y between (0," << m_rows - 1 << ") = " << randomY << "\n";
		if (m_tileArray[randomY][randomX]->getValue() == -1)
		{
			std::cout << "Repeat tile... Trying again\n";
		}
		else if (false)
		{
			std::cout << "Adjacent tile... Trying again\n"; //!checkAdjacentInts(randomX, m_selectedTileX) && randomY == m_selectedTileY
															// check these
		}
		else
		{
			m_tileArray[randomY][randomX]->setValue(-1);
			m_bombsLeft--;
			std::cout << m_bombsLeft << " bombs left...\n";
		}
	}
}

bool Tileset::checkAdjacentInts(int firstInt, int secondInt)
{
	if (firstInt == secondInt - 1 || firstInt == secondInt + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
