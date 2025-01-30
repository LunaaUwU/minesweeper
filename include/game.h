#pragma once
#include <SFML/Graphics.hpp>

#include "tileset.h"


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init();

    void restart();

private:
    Tileset* tileset = new Tileset();



};
