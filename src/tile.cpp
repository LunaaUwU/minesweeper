#include <tile.h>

void Tile::update(sf::Int32 deltaMS)
{
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !m_isFlagged && m_canClick && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        this->openTile();
        m_canClick = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !m_isOpened && m_canClick && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->flagTile();
        m_canClick = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_canClick = true;
    }
}

void Tile::render(sf::RenderWindow& window)
{
	window.draw(m_tile);
}

void Tile::init()
{
    m_tile.setSize(sf::Vector2f(32.f, 32.f));
    m_tileUnkwnownTexture.loadFromFile("../sprites/Tiles/TileUnknown.png");
    m_tile.setTexture(&m_tileUnkwnownTexture);
    m_tile.setPosition(sf::Vector2f(974.f, 524.f));

    m_tile0Texture.loadFromFile("../sprites/Tiles/Tile0.png");
    m_tile1Texture.loadFromFile("../sprites/Tiles/Tile1.png");
    m_tile2Texture.loadFromFile("../sprites/Tiles/Tile2.png");
    m_tile3Texture.loadFromFile("../sprites/Tiles/Tile3.png");
    m_tile4Texture.loadFromFile("../sprites/Tiles/Tile4.png");
    m_tile5Texture.loadFromFile("../sprites/Tiles/Tile5.png");
    m_tile6Texture.loadFromFile("../sprites/Tiles/Tile6.png");
    m_tile7Texture.loadFromFile("../sprites/Tiles/Tile7.png");
    m_tile8Texture.loadFromFile("../sprites/Tiles/Tile8.png");
    m_tileFlagTexture.loadFromFile("../sprites/Tiles/TileFlag.png");
    m_tileMineTexture.loadFromFile("../sprites/Tiles/TileMine.png");

}

void Tile::restart()
{

}

void Tile::changeTile(int value)
{
    switch (value)
    {
        case 1:
        {
            m_tile.setTexture(&m_tile1Texture);
            break;
        }
        case 2:
        {
            m_tile.setTexture(&m_tile2Texture);
            break;
        }
        case 3:
        {
            m_tile.setTexture(&m_tile3Texture);
            break;
        }
        case 4:
        {
            m_tile.setTexture(&m_tile4Texture);
            break;
        }
        case 5:
        {
            m_tile.setTexture(&m_tile5Texture);
            break;
        }
        case 6:
        {
            m_tile.setTexture(&m_tile6Texture);
            break;
        }
        case 7:
        {
            m_tile.setTexture(&m_tile7Texture);
            break;
        }
        case 8:
        {
            m_tile.setTexture(&m_tile8Texture);
            break;
        }
        case -1:
        {
            m_tile.setTexture(&m_tileMineTexture);
            break;
        }
        case 9:
        {
            m_tile.setTexture(&m_tileUnkwnownTexture);
            break;
        }
        case 10:
        {
            m_tile.setTexture(&m_tileFlagTexture);
            break;
        }
		default:
	    {
            m_tile.setTexture(&m_tile0Texture);
            break;
	    }
    }
	
}

void Tile::openTile()
{
    this->changeTile(m_value);
    m_isOpened = true;
}

void Tile::flagTile()
{
    if (!m_isFlagged)
    {
        this->changeTile(10);
    }
    else
    {
        this->changeTile(9);
    }
    m_isFlagged = !m_isFlagged;
    
}
