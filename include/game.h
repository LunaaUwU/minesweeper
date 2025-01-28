#pragma once
#include <SFML/Graphics.hpp>

#include "tile.h" // Cambiar por Board.h cuando esté listo


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init();

    void restart();

private:
    Tile* tile = new Tile();



};
