#include "tile.h"

#include "game.h"
#include "tileset.h"

//void Tile::update(sf::Int32 deltaMS)
//{
//    
//}

void Tile::render(sf::RenderWindow& window)
{
    if (m_active)
		window.draw(m_tile);

    if (m_isSelected)
    {
        m_select.setPosition(m_tile.getPosition().x, m_tile.getPosition().y);
        window.draw(m_select);
    }
}

void Tile::init()
{
    m_tile.setSize(sf::Vector2f(32.f, 32.f));
    m_tileUnkwnownTexture.loadFromFile("../sprites/tiles/TileUnknown.png");
    m_tile.setTexture(&m_tileUnkwnownTexture);

    m_tile0Texture.loadFromFile("../sprites/tiles/Tile0.png");
    m_tile1Texture.loadFromFile("../sprites/tiles/Tile1.png");
    m_tile2Texture.loadFromFile("../sprites/tiles/Tile2.png");
    m_tile3Texture.loadFromFile("../sprites/tiles/Tile3.png");
    m_tile4Texture.loadFromFile("../sprites/tiles/Tile4.png");
    m_tile5Texture.loadFromFile("../sprites/tiles/Tile5.png");
    m_tile6Texture.loadFromFile("../sprites/tiles/Tile6.png");
    m_tile7Texture.loadFromFile("../sprites/tiles/Tile7.png");
    m_tile8Texture.loadFromFile("../sprites/tiles/Tile8.png");
    m_tile9Texture.loadFromFile("../sprites/tiles/Tile9.png");
    m_tileFlagTexture.loadFromFile("../sprites/tiles/TileFlag.png");
    m_tileWrongFlagTexture.loadFromFile("../sprites/tiles/TileWrongFlag.png");
    m_tileMineTexture.loadFromFile("../sprites/tiles/TileMine.png");
    m_tileRedMineTexture.loadFromFile("../sprites/tiles/TileExploded.png");
    m_tileColumnTexture.loadFromFile("../sprites/tiles/TileColumn.png");
    m_tileRowTexture.loadFromFile("../sprites/tiles/TileRow.png");


    m_select.setSize(sf::Vector2f(32.f, 32.f));
    m_selectTexture.loadFromFile("../sprites/tiles/Select.png");
    m_select.setTexture(&m_selectTexture);

}

void Tile::activate(const int posX, const int posY)
{
    m_tile.setPosition(posX, posY);
    m_active = true;
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
        case 9:
        {
            m_tile.setTexture(&m_tile9Texture);
            break;
        }
        case -1:
        {
            m_tile.setTexture(&m_tileMineTexture);
            break;
        }
		case -2:
		{
            m_tile.setTexture(&m_tileRedMineTexture);
            break;
		}
        case 10:
        {
            m_tile.setTexture(&m_tileUnkwnownTexture);
            break;
        }
        case 11:
        {
            m_tile.setTexture(&m_tileFlagTexture);
            break;
        }
		case 12:
		{
            m_tile.setTexture(&m_tileWrongFlagTexture);
            break;
        }
        case 13:
        {
            m_tile.setTexture(&m_tileColumnTexture);
            break;
        }
        case 14:
        {
            m_tile.setTexture(&m_tileRowTexture);
            break;
        }
		default:
	    {
            m_tile.setTexture(&m_tile0Texture);
            break;
	    }
    }
	
}

void Tile::openTile(bool isOpenedManually)
{
    this->changeTile(m_value);
    m_isOpened = true;
    if (m_value == -1 && m_isOnBoard)
    {
        if (isOpenedManually)
        {
            changeTile(-2); // Change the one you click to a red one
            m_value = -2;
        }
			
        Tileset::gameWon = false;
        Tileset::gameFinished = true;
    }
}

void Tile::flagTile()
{
    if (!m_isFlagged)
    {
        this->changeTile(11);
    }
    else
    {
        this->changeTile(10);
    }
    m_isFlagged = !m_isFlagged;
    
}

void Tile::select()
{
    m_isSelected = !m_isSelected;
}
