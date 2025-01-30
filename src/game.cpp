#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    tileset->update(deltaMS);
}

void Game::render(sf::RenderWindow& window)
{
    
    window.clear();

    tileset->render(window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }

    window.display();
}

void Game::init()
{
    tileset->init(2, 2);

    tileset->activate(928, 508);
    tileset->activate(960, 508);
    tileset->activate(928, 540);
    tileset->activate(960, 540);
}

void Game::restart()
{
    tileset->restart();
}
