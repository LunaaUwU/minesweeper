#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    tile->update(deltaMS);
}

void Game::render(sf::RenderWindow& window)
{
    
    window.clear();

    tile->render(window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }

    window.display();
}

void Game::init()
{
    tile->init();
}

void Game::restart()
{
    tile->restart();
}
