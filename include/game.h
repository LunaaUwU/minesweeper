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

    int m_rows = 0;
    int m_columns = 0;

    int m_firstSpawnPosX = 0; // terminar esto
    int m_firstSpawnPosY = 0;

    int m_spawnPosX = 0;
    int m_spawnPosY = 0;

    int m_rowNumber = 0;

};
