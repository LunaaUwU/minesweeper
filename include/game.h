#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <random>
#include "tileset.h"
#include "soggy.h"


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void init();

    void instantiate();

    void restart();

    inline static bool closeGame = false;

    inline static bool gameOver = false;

    inline static bool canClick = true;

private:

    void updateDifficultyCounters();

    int randomInt(int min, int max);

    Tileset* m_tileset = new Tileset();

    bool m_isMainMenuActive = true;
    bool m_mainMenuSelection = true; // true = Play, false = Quit

    bool m_isPauseMenuActive = false;
    bool m_pauseMenuSelection = true; // true = Resume, false = Quit

    bool m_isDifficultyMenuActive = false;
    int m_difficultyMenuSelection = 0; // 0 = rows, 1 = cols, 2 = Bombs, 3 = Start

    int m_rows = 10;
    int m_columns = 15;

    int m_numberOfBombs = 30;

    int m_firstSpawnPosX = 0;
    int m_firstSpawnPosY = 0;

    int m_spawnPosX = 0;
    int m_spawnPosY = 0;

    int m_columnNumber = 0;

    int m_menuSongNum = 6;
    int m_gameSongNum = 10;

    sf::Sprite m_mainMenuPlaySprite;
    sf::Texture m_mainMenuPlayTexture;
    sf::Sprite m_mainMenuQuitSprite;
    sf::Texture m_mainMenuQuitTexture;

    sf::Sprite m_pauseMenuResumeSprite;
    sf::Texture m_pauseMenuResumeTexture;
    sf::Sprite m_pauseMenuQuitSprite;
    sf::Texture m_pauseMenuQuitTexture;

    sf::Sprite m_difficultyMenuSprite;
    sf::Texture m_difficultyMenuTexture;
    sf::Sprite m_difficultyMenuStartSprite;
    sf::Texture m_difficultyMenuStartTexture;

    sf::Music m_menuMusic;
    sf::Music m_gameMusic;
    sf::Music m_sogMusic;

    Tile* m_difficultyColumn = new Tile();
    Tile* m_difficultyRow = new Tile();
    Tile* m_difficultyBomb = new Tile();

    Tile* m_difficultyColumnNum1 = new Tile();
    Tile* m_difficultyColumnNum2 = new Tile();

    Tile* m_difficultyRowNum1 = new Tile();
    Tile* m_difficultyRowNum2 = new Tile();

    Tile* m_difficultyBombNum1 = new Tile();
    Tile* m_difficultyBombNum2 = new Tile();

    bool m_canQuit = true;
    bool m_canMove = true;
    bool m_canSog = true;
    bool m_isSogging = false;

    std::vector<Soggy*> m_sogArray;

    std::random_device rd;

};
