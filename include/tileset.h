#pragma once
#include <SFML/Graphics.hpp>

#include <Tile.h>

class Tileset
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init(int numberToInstantiate);

    void instantiate(int rows, int columns);

    void activate(int posX, int posY);

    void restart();


private:

    std::vector<Tile*> m_tileSet;

    std::vector<std::vector<Tile*>> m_tileArray;

    int m_allInstantiatedTiles = 0;

};