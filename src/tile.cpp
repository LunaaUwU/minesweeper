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

void Tile::init(sf::Texture& tileUnkwnownTexture, sf::Texture& tile0Texture, sf::Texture& tile1Texture, sf::Texture& tile2Texture, sf::Texture& tile3Texture, sf::Texture& tile4Texture,
    sf::Texture& tile5Texture, sf::Texture& tile6Texture, sf::Texture& tile7Texture, sf::Texture& tile8Texture, sf::Texture& tile9Texture, sf::Texture& tileFlagTexture, sf::Texture& tileWrongFlagTexture,
    sf::Texture& tileMineTexture, sf::Texture& tileRedMineTexture, sf::Texture& tileColumnTexture, sf::Texture& tileRowTexture, sf::Texture& selectTexture)
{
    m_tileUnkwnownTexture = tileUnkwnownTexture;
    m_tile0Texture = tile0Texture;
    m_tile1Texture = tile1Texture;
    m_tile2Texture = tile2Texture;
    m_tile3Texture = tile3Texture;
    m_tile4Texture = tile4Texture;
    m_tile5Texture = tile5Texture;
    m_tile6Texture = tile6Texture;
    m_tile7Texture = tile7Texture;
    m_tile8Texture = tile8Texture;
    m_tile9Texture = tile9Texture;
    m_tileFlagTexture = tileFlagTexture;
    m_tileWrongFlagTexture = tileWrongFlagTexture;
    m_tileMineTexture = tileMineTexture;
    m_tileRedMineTexture = tileRedMineTexture;
    m_tileColumnTexture = tileColumnTexture;
    m_tileRowTexture = tileRowTexture;
    m_selectTexture = selectTexture;

    m_tile.setSize(sf::Vector2f(32.f, 32.f));
    m_tile.setTexture(&m_tileUnkwnownTexture);


    m_select.setSize(sf::Vector2f(32.f, 32.f));
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
