#pragma once
#include <SFML/Graphics.hpp>

#include "tile.h"

class Game;

class Tileset
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void init(int rows, int columns, int numberOfBombs);

    void activate(int posX, int posY) const;

    void restart();

    void fillBombs();

    void fillNumbers() const;

    void checkTilesAround();

    void openTilesAround() const;

    void checkFlagsAround();

    void spawnBombCounter(int posX, int posY);

    void updateBombCounter();

    bool checkWin() const;

    std::vector<std::vector<Tile*>> getTileArray() { return m_tileArray; }

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

    
    bool m_canClickHorizontal = true;
    bool m_canClickVertical = true;

    int m_selectedTileX = 0;
    int m_selectedTileY = 0;

    sf::Vector2i m_tileToOpenPos;

    Tile* m_bombCounterBomb = new Tile();
    Tile* m_bombCounterTile1 = new Tile();
    Tile* m_bombCounterTile2 = new Tile();

};