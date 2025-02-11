#pragma once
#include <SFML/Graphics.hpp>

#include "tileset.h"


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window);

    void init();

    void instantiate();

    void restart();

    inline static bool closeGame = false;

    inline static bool gameOver = false;

    inline static bool canClick = true;

private:

    Tileset* m_tileset = new Tileset();

    bool m_gameOver = false;

    bool m_isMainMenuActive = true;
    bool m_mainMenuSelection = true; // true == Play, false == Quit

    int m_rows = 0;
    int m_columns = 0;

    int m_numberOfBombs = 0;

    int m_firstSpawnPosX = 0;
    int m_firstSpawnPosY = 0;

    int m_spawnPosX = 0;
    int m_spawnPosY = 0;

    int m_columnNumber = 0;

    sf::Sprite m_mainMenuPlaySprite;
    sf::Texture m_mainMenuPlayTexture;
    sf::Sprite m_mainMenuQuitSprite;
    sf::Texture m_mainMenuQuitTexture;

};
