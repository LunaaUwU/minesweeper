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
    m_rows = 10;
    m_columns = 10;

    m_tileset->init(m_rows, m_columns);

    m_firstSpawnPosX = 960 - (m_columns * 16);

    m_firstSpawnPosY = 540 - (m_rows * 16);

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
}

void Game::restart()
{
    m_tileset->restart();
}
