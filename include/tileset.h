#pragma once
#include <SFML/Graphics.hpp>

#include <Tile.h>

class Tileset
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init(int rows, int columns);

    void instantiate();

    void activate(int posX, int posY);

    void restart();

    std::vector<std::vector<Tile*>> getTileArray() { return m_tileArray; }


private:

    std::vector<std::vector<Tile*>> m_tileArray;

    int m_allInstantiatedTiles = 0;

    int m_rows = 0;
    int m_columns = 0;

    bool m_canClickHorizontal = true;
    bool m_canClickVertical = true;

    int m_selectedTileX = 0;
    int m_selectedTileY = 0;

};