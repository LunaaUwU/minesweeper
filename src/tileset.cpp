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
		if (!m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen())
		{
			m_tileArray[m_selectedTileX][m_selectedTileY]->openTile();
			if (m_isFirstTile)
			{
				fillBombs();
				fillNumbers();
				m_isFirstTile = false;
			}
		}
		else if (m_tileArray[m_selectedTileX][m_selectedTileY]->getValue() != 0 && m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen())
		{
			checkFlagsAround();
			if (m_hasBeenFlagged == true)
			{
				openTilesAround();
			}
		}
		

		checkTilesAround();
		while (m_hasNoEmptyTiles == false)
		{
			if (m_hasNoEmptyTiles == false)
			{
				openTilesAround();
			}
			checkTilesAround();
		}
		m_canClick = false;
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
	std::uniform_int_distribution<int> distribX(0, m_rows - 1);
	std::uniform_int_distribution<int> distribY(0, m_columns - 1);
	int randomX = 0;
	int randomY = 0;
	while (m_bombsLeft > 0)
	{
		randomX = distribX(gen);
		randomY = distribY(gen);

		std::cout << "Selected tile is: (" << m_selectedTileX << "," << m_selectedTileY << ")\n";
		std::cout << "Random X between (0," << m_rows - 1 << ") = " << randomX << "\n";
		std::cout << "Random Y between (0," << m_columns - 1 << ") = " << randomY << "\n";
		if (m_tileArray[randomX][randomY]->getValue() == -1)
		{
			std::cout << "Repeat tile... Trying again\n";
		}
		else if (((randomY == m_selectedTileY - 1 || randomY == m_selectedTileY || randomY == m_selectedTileY + 1) && randomX == m_selectedTileX) || ((randomY == m_selectedTileY - 1 || randomY == m_selectedTileY || randomY == m_selectedTileY + 1) && randomX == m_selectedTileX + 1) || ((randomY == m_selectedTileY - 1 || randomY == m_selectedTileY || randomY == m_selectedTileY + 1) && randomX == m_selectedTileX - 1))
		{
			std::cout << "Adjacent tile... Trying again\n";
		}
		else
		{
			m_tileArray[randomX][randomY]->setValue(-1);
			m_bombsLeft--;
			std::cout << m_bombsLeft << " bombs left...\n";
		}
	}
}

void Tileset::fillNumbers()
{
	for (int i = 0; i < m_tileArray.size(); i++)
	{
		for (int j = 0; j < m_tileArray[i].size(); j++)
		{
			if (m_tileArray[i][j]->getValue() != -1)
			{
				if (i == 0) // Up row
				{
					if (j == 0) // Left column
					{
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else if (j == m_columns - 1) // Right column
					{
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else
					{
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
				}
				else if (i == m_rows - 1) // Down row
				{
					if (j == 0) // Left column
					{
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else if (j == m_columns - 1) // Right columns
					{
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else
					{
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
				}
				else
				{
					if (j == 0) // Left column, no corners
					{
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else if (j == m_columns - 1) // Right column, no corners
					{
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
					else // Everything inside
					{
						if (m_tileArray[i-1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i-1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j+1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i+1][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
						if (m_tileArray[i][j-1]->getValue() == -1)
						{
							m_tileArray[i][j]->setValue(m_tileArray[i][j]->getValue() + 1);
						}
					}
				}
			}
		}
	}
}

void Tileset::checkTilesAround()
{
	for (int i = 0; i < m_tileArray.size(); i++)
	{
		for (int j = 0; j < m_tileArray[i].size(); j++)
		{
			if (m_tileArray[i][j]->getValue() == 0 && !m_tileArray[i][j]->getHasOpenedAround() && m_tileArray[i][j]->getIsOpen())
			{
				m_hasNoEmptyTiles = false;
				std::cout << "Empty file not opened found\n";
				m_tileToOpenPos.x = i;
				m_tileToOpenPos.y = j;
				return;
			}
		}
	}
	m_hasNoEmptyTiles = true;
}

void Tileset::openTilesAround()
{
	std::cout << "Opening tiles around...\n";
	Tile* tileToOpen;
	m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y]->setHasOpenedAround(true);
	if (m_tileToOpenPos.x == 0) // Up row
	{
		if (m_tileToOpenPos.y == 0) // Left column
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right column
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
	}
	else if (m_tileToOpenPos.x == m_rows - 1) // Down row
	{
		if (m_tileToOpenPos.y == 0) // Left column
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right columns
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
	}
	else
	{
		if (m_tileToOpenPos.y == 0) // Left column, no corners
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right column, no corners
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
		else // Everything inside
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile();
			}
		}
	}
	m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y]->setHasOpenedAround(true);
}

void Tileset::checkFlagsAround()
{
	int flagsAround = 0;
	std::cout << "Checking flags around tile of value " << m_tileArray[m_selectedTileX][m_selectedTileY]->getValue() << "\n";

	if (m_selectedTileX == 0) // Up row
	{
		if (m_selectedTileY == 0) // Left column
		{
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else if (m_selectedTileY == m_columns - 1) // Right column
		{
			if (m_tileArray[m_selectedTileX][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else
		{
			if (m_tileArray[m_selectedTileX][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
		}
	}
	else if (m_selectedTileX == m_rows - 1) // Down row
	{
		if (m_selectedTileY == 0) // Left column
		{
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else if (m_selectedTileY == m_columns - 1) // Right column
		{
			if (m_tileArray[m_selectedTileX][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else
		{
			if (m_tileArray[m_selectedTileX][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
		}
	}
	else
	{
		if (m_selectedTileY == 0) // Left column, no corners
		{
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY+1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else if (m_selectedTileY == m_columns - 1) // Right column, no corners
		{
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX-1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY-1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX+1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
		}
		else// Everything else
		{
			if (m_tileArray[m_selectedTileX - 1][m_selectedTileY - 1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX - 1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX - 1][m_selectedTileY + 1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY + 1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX + 1][m_selectedTileY + 1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX + 1][m_selectedTileY]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX + 1][m_selectedTileY - 1]->getIsFlagged())
			{
				flagsAround++;
			}
			if (m_tileArray[m_selectedTileX][m_selectedTileY - 1]->getIsFlagged())
			{
				flagsAround++;
			}
		}
	}
	std::cout << flagsAround << " flags found\n";
	if (flagsAround == m_tileArray[m_selectedTileX][m_selectedTileY]->getValue())
	{
		m_hasBeenFlagged = true;
		m_tileToOpenPos.x = m_selectedTileX;
		m_tileToOpenPos.y = m_selectedTileY;
	}
	else
	{
		m_hasBeenFlagged = false;
	}
}
