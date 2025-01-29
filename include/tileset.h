#pragma once
#include <SFML/Graphics.hpp>

#include <Tile.h>

class Tileset
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init(int numberToInstantiate);

    void restart();

    void activate();


private:
    std::vector<Tile*> m_tileArray;



};