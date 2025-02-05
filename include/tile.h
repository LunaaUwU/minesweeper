#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:

    /*void update(sf::Int32 deltaMS);*/

    void render(sf::RenderWindow& window);

    void init();

    void restart();

    void activate(int posX, int posY);

    void changeTile(int value);

    void openTile();

    void flagTile();

    void select();

    bool getActive() const { return m_active; }

    bool getIsOpen() const { return m_isOpened; }

    bool getIsFlagged() const { return m_isFlagged; }

    int getValue() const { return m_value; }

    bool getHasOpenedAround() const { return m_hasOpenedAround; }

    void setHasOpenedAround(const bool hasOpenedAround) { m_hasOpenedAround = hasOpenedAround; }

    void setValue(const int value) { m_value = value; }

private:

    bool m_isOpened = false;
    bool m_isFlagged = false;
    int m_value = 0; // 0, 1, 2, 3, 4, 5, 6, 7, 8 are numbers, -1 is bomb, 9 is unknown and 10 is flag

    bool m_active = false;

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
    sf::Texture m_tileFlagTexture;
    sf::Texture m_tileMineTexture;

    sf::RectangleShape m_select;

    sf::Texture m_selectTexture;


};