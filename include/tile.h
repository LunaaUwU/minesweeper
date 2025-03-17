#pragma once
#include <SFML/Graphics.hpp>

class Game;
class Tileset;

class Tile
{
public:

    /*void update(sf::Int32 deltaMS);*/

    void render(sf::RenderWindow& window);

    void init();

    void activate(int posX, int posY);

    void changeTile(int value);

    void openTile(bool isOpenedManually);

    void flagTile();

    void select();

    bool getActive() const { return m_active; }

    bool getIsOpen() const { return m_isOpened; }

    bool getIsFlagged() const { return m_isFlagged; }

    int getValue() const { return m_value; }

    bool getHasOpenedAround() const { return m_hasOpenedAround; }

    bool getIsSelected() const { return m_isSelected; }

    void setActive(const bool active) { m_active = active; }

    void setHasOpenedAround(const bool hasOpenedAround) { m_hasOpenedAround = hasOpenedAround; }

    void setValue(const int value) { m_value = value; }

    void setPosition(int posX, int posY) { m_tile.setPosition(posX, posY); }

    void setIsOnBoard(const bool value) { m_isOnBoard = value; }

private:

    bool m_isOpened = false;
    bool m_isFlagged = false;
    int m_value = 0; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 are numbers (yes, 9 too for decoration)
	//                 -1 is bomb, 10 is unknown, 11 is flag and 12 is transparent flag. 13 and 14 are row and column decorations

    bool m_active = false;

    bool m_isOnBoard = true; // To differentiate the tiles that are used for decoration purposes

    bool m_hasOpenedAround = false;

    bool m_isSelected = false;

    sf::RectangleShape m_tile;

    sf::Texture m_tileUnkwnownTexture;
    sf::Texture m_tile0Texture;
    sf::Texture m_tile1Texture;
    sf::Texture m_tile2Texture;
    sf::Texture m_tile3Texture;
    sf::Texture m_tile4Texture;
    sf::Texture m_tile5Texture;
    sf::Texture m_tile6Texture;
    sf::Texture m_tile7Texture;
    sf::Texture m_tile8Texture;
    sf::Texture m_tile9Texture;
    sf::Texture m_tileFlagTexture;
    sf::Texture m_tileWrongFlagTexture;
    sf::Texture m_tileMineTexture;
    sf::Texture m_tileRedMineTexture;
    sf::Texture m_tileColumnTexture;
    sf::Texture m_tileRowTexture;

    sf::RectangleShape m_select;

    sf::Texture m_selectTexture;


};