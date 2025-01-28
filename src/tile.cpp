#include <tile.h>

void Tile::update(sf::Int32 deltaMS)
{

}

void Tile::render(sf::RenderWindow& window)
{
	window.draw(m_tile);
}

void Tile::init()
{
    m_tile.setSize(sf::Vector2f(32.f, 32.f));
    m_tileTexture.loadFromFile("../sprites/Tiles/TileUnknown.png");
    m_tile.setTexture(&m_tileTexture);
    m_tile.setPosition(sf::Vector2f(896.f, 752.f));
}

void Tile::restart()
{

}
