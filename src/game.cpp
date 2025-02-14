#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    // Split update behaviour depending on the menu
    if (m_isMainMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_mainMenuSelection = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_mainMenuSelection = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
	        if (m_mainMenuSelection)
	        {
                m_isMainMenuActive = false;
                m_isDifficultyMenuActive = true;
	        }
            else
            {
                closeGame = true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            closeGame = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }
    else if (m_isDifficultyMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_canMove)
        {
            m_difficultyMenuSelection++;
            if (m_difficultyMenuSelection >= 4)
                m_difficultyMenuSelection = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_canMove)
        {
            m_difficultyMenuSelection--;
            if (m_difficultyMenuSelection < 0)
                m_difficultyMenuSelection = 3;
        }
	    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && canClick && m_difficultyMenuSelection == 2)
	    {
            m_isDifficultyMenuActive = false;
            instantiate();
	    }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_canMove = true;
        }
        else
        {
            m_canMove = false;
        }
    }
    else if (m_isPauseMenuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_pauseMenuSelection = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_pauseMenuSelection = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
	        if (m_pauseMenuSelection)
	        {
                m_isPauseMenuActive = false;
	        }
            else
            {
                m_canQuit = false;
                restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            m_canQuit = false;
            restart();
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }
    else
    {
        m_tileset->update(deltaMS);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_canQuit)
        {
            m_canQuit = false;
            m_isPauseMenuActive = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_canQuit = true;
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        canClick = true;
    }
    else
    {
        canClick = false;
    }

    if (gameOver)
    {
        restart();
    }
}

void Game::render(sf::RenderWindow& window) const
{
    
    window.clear();

    if (closeGame)
    {
        window.close();
    }

    if (m_isMainMenuActive)
    {
	    if (m_mainMenuSelection)
	    {
            window.draw(m_mainMenuPlaySprite);
	    }
        else
        {
            window.draw(m_mainMenuQuitSprite);
        }
    }
    else if (m_isDifficultyMenuActive)
    {
	    if (m_difficultyMenuSelection == 3)
	    {
            window.draw(m_difficultyMenuStartSprite);
	    }
        else
        {
            window.draw(m_difficultyMenuSprite);
        }
    }
    else if (m_isPauseMenuActive)
    {
	    if (m_pauseMenuSelection)
	    {
            window.draw(m_pauseMenuResumeSprite);
	    }
        else
        {
            window.draw(m_pauseMenuQuitSprite);
        }
    }
    else
    {
        m_tileset->render(window);
    }

    window.display();
}

void Game::init()
{
    m_mainMenuPlayTexture.loadFromFile("../sprites/menu/main_menu_play.png");
    m_mainMenuPlaySprite.setTexture(m_mainMenuPlayTexture);
    m_mainMenuPlaySprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_mainMenuQuitTexture.loadFromFile("../sprites/menu/main_menu_quit.png");
    m_mainMenuQuitSprite.setTexture(m_mainMenuQuitTexture);
    m_mainMenuQuitSprite.setPosition(sf::Vector2f(0.f, 0.f));

    m_pauseMenuResumeTexture.loadFromFile("../sprites/menu/pause_menu_resume.png");
    m_pauseMenuResumeSprite.setTexture(m_pauseMenuResumeTexture);
    m_pauseMenuResumeSprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_pauseMenuQuitTexture.loadFromFile("../sprites/menu/pause_menu_quit.png");
    m_pauseMenuQuitSprite.setTexture(m_pauseMenuQuitTexture);
    m_pauseMenuQuitSprite.setPosition(sf::Vector2f(0.f, 0.f));

    m_difficultyMenuTexture.loadFromFile("../sprites/menu/difficulty_menu.png");
    m_difficultyMenuSprite.setTexture(m_difficultyMenuTexture);
    m_difficultyMenuSprite.setPosition(sf::Vector2f(0.f, 0.f));
    m_difficultyMenuStartTexture.loadFromFile("../sprites/menu/difficulty_menu_start.png");
    m_difficultyMenuStartSprite.setTexture(m_difficultyMenuStartTexture);
    m_difficultyMenuStartSprite.setPosition(sf::Vector2f(0.f, 0.f));
}

void Game::instantiate()
{
    m_rows = 10;
    m_columns = 15;

    m_numberOfBombs = 30;

    m_tileset->init(m_rows, m_columns, m_numberOfBombs);

    m_firstSpawnPosX = 960 - (m_columns * 16);

    //                 540
    m_firstSpawnPosY = 636 - (m_rows * 16);

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

    m_tileset->getTileArray()[0][0]->select();

    // Bomb counter

    m_tileset->spawnBombCounter(896, m_firstSpawnPosY - 96);
}

void Game::restart()
{
    m_isMainMenuActive = true;
    m_mainMenuSelection = true;
    m_isPauseMenuActive = false;
    m_pauseMenuSelection = true;
    m_isDifficultyMenuActive = false;
    m_difficultyMenuSelection = 0;
    gameOver = false;
    m_tileset->restart();
    instantiate();
}
