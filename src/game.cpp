#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    m_tileset->update(deltaMS);
}

void Game::render(sf::RenderWindow& window)
{
    
    window.clear();

    m_tileset->render(window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }

    window.display();
}

void Game::init()
{
    m_rows = 16;
    m_columns = 2;

    m_tileset->init(m_rows, m_columns);

    // 1920/2 = 960
	if (m_rows % 2 == 0)
	{
        // 960 = 960
        m_firstSpawnPosX = 960 - m_rows * 32;
	}
    else
    {
        // 960+16 = 976
        m_firstSpawnPosX = 976 - m_rows * 32; // probablemente se mueva por el *32
    }

    // 1080/2 = 540
    if (m_columns % 2 == 0)
    {
	    // 540 = 540
        m_firstSpawnPosY = 540 - m_columns * 32;
    }
    else
    {
        // 540+16 = 556
        m_firstSpawnPosY = 556 - m_columns * 32;
    }

    m_spawnPosX = m_firstSpawnPosX;
    m_spawnPosY = m_firstSpawnPosY;
    
    for (int i = 0; i < m_rows * m_columns; i++)
    {
        m_tileset->activate(m_spawnPosX, m_spawnPosY);
        if (m_columnNumber + 1 == m_columns)
        {
            m_spawnPosX = m_firstSpawnPosX;
            m_spawnPosY += 32;
            m_columnNumber = -1;
        }
        else
        {
            m_spawnPosX += 32;
        }
        m_columnNumber++;
    }
    
    m_tileset->activate(960, 508);
    m_tileset->activate(928, 540);
    m_tileset->activate(960, 540);
}

void Game::restart()
{
    m_tileset->restart();
}
