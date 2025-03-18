#pragma once
#include <SFML/Graphics.hpp>

#include "tile.h"

class Game;

class Tileset
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void init(int rows, int columns, int numberOfBombs, sf::Texture& tileUnkwnownTexture, sf::Texture& tile0Texture, sf::Texture& tile1Texture, sf::Texture& tile2Texture, sf::Texture& tile3Texture, sf::Texture& tile4Texture,
        sf::Texture& tile5Texture, sf::Texture& tile6Texture, sf::Texture& tile7Texture, sf::Texture& tile8Texture, sf::Texture& tile9Texture, sf::Texture& tileFlagTexture, sf::Texture& tileWrongFlagTexture,
        sf::Texture& tileMineTexture, sf::Texture& tileRedMineTexture, sf::Texture& tileColumnTexture, sf::Texture& tileRowTexture, sf::Texture& selectTexture);

    void activate(int posX, int posY) const;

    void restart();

    void fillBombs();

    void fillNumbers() const;

    void checkTilesAround();

    void openTilesAround() const;

    void checkFlagsAround();

    void spawnBombCounter(int posX, int posY);

    void updateBombCounter() const;

    bool checkWin() const;

    std::vector<std::vector<Tile*>> getTileArray() { return m_tileArray; }


    inline static bool gameFinished = false;

    inline static bool gameWon = false; // Wheter you won or lost

private:

    std::vector<std::vector<Tile*>> m_tileArray;

    int m_allInstantiatedTiles = 0;

    int m_rows = 0;
    int m_columns = 0;

    int m_numberOfBombs = 0;
    int m_bombsLeft = 0;

    bool m_isFirstTile = true;
    bool m_hasNoEmptyTiles = true;
    bool m_hasBeenFlagged = false;

    
    bool m_canClickRight = true;
    bool m_canClickLeft = true;
    bool m_canClickUp = true;
    bool m_canClickDown = true;

    int m_selectedTileX = 0;
    int m_selectedTileY = 0;

    sf::Vector2i m_tileToOpenPos;

    Tile* m_bombCounterBomb = new Tile();
    Tile* m_bombCounterTile1 = new Tile();
    Tile* m_bombCounterTile2 = new Tile();

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
    sf::Texture m_selectTexture;

    bool m_doOnce = true;
    bool m_doOnce2 = true;

};