#include <iostream>
#include "tileset.h"
#include "game.h"

#include <random>

void Tileset::update(sf::Int32 deltaMS)
{
	/*for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->update(deltaMS);
		}
	}*/

	if (!gameFinished)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !m_tileArray[m_selectedTileX][m_selectedTileY]->getIsFlagged() && Game::canClickZ && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if (!m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen())
			{
				m_tileArray[m_selectedTileX][m_selectedTileY]->openTile(true);
				if (m_isFirstTile)
				{
					fillBombs();
					fillNumbers();
					m_isFirstTile = false;
				}
			}
			else if (m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen())
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
			Game::canClickZ = false;

			if (checkWin())
			{
				gameFinished = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !m_tileArray[m_selectedTileX][m_selectedTileY]->getIsOpen() && Game::canClickZ && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (m_tileArray[m_selectedTileX][m_selectedTileY]->getIsFlagged())
				m_numberOfBombs++;
			else
				m_numberOfBombs--;
			m_tileArray[m_selectedTileX][m_selectedTileY]->flagTile();

			updateBombCounter();

			Game::canClickZ = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			Game::canClickZ = true;
		}
	}
	else
	{
		if (m_doOnce) // Until you un-press Z or whatever you opened the last tile with
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				Game::canClickZ = false;
				// checks if you won or lost
				if (m_doOnce2)
				{
					if (!gameWon)
					{
						for (std::vector<Tile*> row : m_tileArray)
						{
							for (Tile* tile : row)
							{
								if (tile->getValue() == -1 && !tile->getIsOpen() && !tile->getIsFlagged())
									tile->openTile(false);
								else if (tile->getIsFlagged() && tile->getValue() != -1)
									tile->changeTile(12);
							}
						}
						m_bombCounterBomb->changeTile(-2);
					}
					m_doOnce2 = false;
				}
				
			}
			else
			{
				m_doOnce = false;
			}
		}
		else
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && Game::canClickZ)
			{
				Game::gameOver = true;
			}
		}
	}
	

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && m_canClickRight)
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
			m_canClickRight = false;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && m_canClickLeft)
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
			m_canClickLeft = false;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && m_canClickDown)
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
			m_canClickDown = false;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && m_canClickUp)
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
			m_canClickUp = false;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_canClickRight = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_canClickLeft = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_canClickUp = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_canClickDown = true;
	}
}

void Tileset::render(sf::RenderWindow& window) const
{
	for (const std::vector<Tile*> &row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			tile->render(window);
		}
	}

	m_bombCounterTile1->render(window);
	m_bombCounterTile2->render(window);
	m_bombCounterBomb->render(window);
}

void Tileset::init(const int rows, const int columns, const int numberOfBombs, sf::Texture& tileUnkwnownTexture, sf::Texture& tile0Texture, sf::Texture& tile1Texture, sf::Texture& tile2Texture, sf::Texture& tile3Texture, sf::Texture& tile4Texture,
	sf::Texture& tile5Texture, sf::Texture& tile6Texture, sf::Texture& tile7Texture, sf::Texture& tile8Texture, sf::Texture& tile9Texture, sf::Texture& tileFlagTexture, sf::Texture& tileWrongFlagTexture,
	sf::Texture& tileMineTexture, sf::Texture& tileRedMineTexture, sf::Texture& tileColumnTexture, sf::Texture& tileRowTexture, sf::Texture& selectTexture)
{

	m_tileUnkwnownTexture = tileUnkwnownTexture;
	m_tile0Texture = tile0Texture;
	m_tile1Texture = tile1Texture;
	m_tile2Texture = tile2Texture;
	m_tile3Texture = tile3Texture;
	m_tile4Texture = tile4Texture;
	m_tile5Texture = tile5Texture;
	m_tile6Texture = tile6Texture;
	m_tile7Texture = tile7Texture;
	m_tile8Texture = tile8Texture;
	m_tile9Texture = tile9Texture;
	m_tileFlagTexture = tileFlagTexture;
	m_tileWrongFlagTexture = tileWrongFlagTexture;
	m_tileMineTexture = tileMineTexture;
	m_tileRedMineTexture = tileRedMineTexture;
	m_tileColumnTexture = tileColumnTexture;
	m_tileRowTexture = tileRowTexture;
	m_selectTexture = selectTexture;

	m_tileArray.resize(rows, std::vector<Tile*>(columns, nullptr)); // Resize the matrix to make it of size (rows, columns)

	m_rows = rows;
	m_columns = columns;
	m_numberOfBombs = numberOfBombs;
	m_bombsLeft = numberOfBombs;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			m_tileArray[i][j] = new Tile(); // Create a tile for each position
			m_tileArray[i][j]->init(tileUnkwnownTexture, tile0Texture, tile1Texture, tile2Texture, tile3Texture, tile4Texture, tile5Texture, tile6Texture, tile7Texture, tile8Texture,
				tile9Texture, tileFlagTexture, tileWrongFlagTexture, tileMineTexture, tileRedMineTexture, tileColumnTexture, tileRowTexture, selectTexture);
		}
	}

	m_allInstantiatedTiles = rows * columns;
}

void Tileset::activate(const int posX, const int posY) const
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
			delete tile;
		}
	}

	m_tileArray.clear();

	gameFinished = false;
	gameWon = false;
	m_doOnce = true;
	m_doOnce2 = true;
	m_isFirstTile = true;

	m_selectedTileX = 0;
	m_selectedTileY = 0;
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

void Tileset::fillNumbers() const
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

void Tileset::openTilesAround() const
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
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right column
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
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
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right columns
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
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
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else if (m_tileToOpenPos.y == m_columns - 1) // Right column, no corners
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
		}
		else // Everything inside
		{
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x - 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y + 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x + 1][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
			}
			tileToOpen = m_tileArray[m_tileToOpenPos.x][m_tileToOpenPos.y - 1];
			if (!tileToOpen->getIsOpen() && !tileToOpen->getIsFlagged())
			{
				tileToOpen->openTile(true);
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
	if (flagsAround >= m_tileArray[m_selectedTileX][m_selectedTileY]->getValue())
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

void Tileset::spawnBombCounter(int posX, int posY)
{

	m_bombCounterBomb->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
		m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
	m_bombCounterTile1->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
		m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);
	m_bombCounterTile2->init(m_tileUnkwnownTexture, m_tile0Texture, m_tile1Texture, m_tile2Texture, m_tile3Texture, m_tile4Texture, m_tile5Texture, m_tile6Texture, m_tile7Texture, m_tile8Texture,
		m_tile9Texture, m_tileFlagTexture, m_tileWrongFlagTexture, m_tileMineTexture, m_tileRedMineTexture, m_tileColumnTexture, m_tileRowTexture, m_selectTexture);

	m_bombCounterBomb->setPosition(posX, posY);
	m_bombCounterTile1->setPosition(posX + 64, posY);
	m_bombCounterTile2->setPosition(posX + 96, posY);

	m_bombCounterBomb->setIsOnBoard(false);
	m_bombCounterTile1->setIsOnBoard(false);
	m_bombCounterTile2->setIsOnBoard(false);

	m_bombCounterBomb->setValue(-1);
	m_bombCounterBomb->openTile(false);

	m_bombCounterTile1->setValue(m_numberOfBombs / 10);
	m_bombCounterTile1->openTile(false);

	m_bombCounterTile2->setValue(m_numberOfBombs - (m_numberOfBombs / 10 * 10));
	m_bombCounterTile2->openTile(false);

	m_bombCounterTile1->setActive(true);
	m_bombCounterTile2->setActive(true);
	m_bombCounterBomb->setActive(true);
}

void Tileset::updateBombCounter() const
{
	if (m_numberOfBombs <= 0)
	{
		m_bombCounterTile1->setValue(0);
		m_bombCounterTile1->changeTile(0);

		m_bombCounterTile2->setValue(0);
		m_bombCounterTile2->changeTile(0);
	}
	else
	{
		m_bombCounterTile1->setValue(m_numberOfBombs / 10);
		m_bombCounterTile1->changeTile(m_bombCounterTile1->getValue());

		m_bombCounterTile2->setValue(m_numberOfBombs - (m_numberOfBombs / 10 * 10));
		m_bombCounterTile2->changeTile(m_bombCounterTile2->getValue());
	}
}


bool Tileset::checkWin() const
{
	for (std::vector<Tile*> row : m_tileArray)
	{
		for (Tile* tile : row)
		{
			if (!tile->getIsOpen() && tile->getValue() != -1)
			{
				return false;
			}
		}
	}

	for (std::vector<Tile*> row : m_tileArray) // Flag all unflagged tiles
	{
		for (Tile* tile : row)
		{
			if (!tile->getIsOpen() && !tile->getIsFlagged())
			{
				tile->flagTile();
			}
		}
	}
	m_bombCounterTile1->changeTile(0);
	m_bombCounterTile2->changeTile(0);
	m_bombCounterBomb->changeTile(11);
	gameWon = true;
	return true;
}

