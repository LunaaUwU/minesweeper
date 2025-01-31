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
    m_rows = 2;
    m_columns = 2;

    m_tileset->init(m_rows, m_columns);

    // 1920/2 = 960
	if (m_rows % 2 == 0)
	{
        // 960-32 = 928
        m_spawnPosX = 928 - m_rows * 32;
	}
    else
    {
        // 960-16 = 944
        m_spawnPosX = 944 - m_rows * 32;
    }

    // 1080/2 = 540
    if (m_columns % 2 == 0)
    {
	    // 540-32 = 508
        m_spawnPosY = 508 - m_columns * 32;
    }
    else
    {
        // 540-16 = 524
        m_spawnPosY = 524 - m_columns * 32;
    }
    
    for (int i = 0; i < m_rows * m_columns; i++)
    {
        m_tileset->activate(m_spawnPosX, m_spawnPosY);
        m_spawnPosX += 32; // terminar esto tambien
    }
    
    m_tileset->activate(960, 508);
    m_tileset->activate(928, 540);
    m_tileset->activate(960, 540);
}

void Game::restart()
{
    m_tileset->restart();
}
