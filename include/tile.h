#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init();

    void restart();

private:
    sf::RectangleShape m_tile;
    sf::Texture m_tileTexture;


};