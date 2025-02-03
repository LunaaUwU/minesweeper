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

    Tileset* m_tileset = new Tileset();

    bool m_gameOver = false;

    int m_rows = 0;
    int m_columns = 0;

    int m_firstSpawnPosX = 0;
    int m_firstSpawnPosY = 0;

    int m_spawnPosX = 0;
    int m_spawnPosY = 0;

    int m_columnNumber = 0;

};
