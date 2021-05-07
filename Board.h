#ifndef BOARD_H
#define BOARD_H 
#include "Tile.h"
#include <vector>


class Board {
private:
    std::vector<std::vector<Tile *>> vectorBoard;
    bool newGame;
    int previouslyAdded[2];
    // std:vector<Coordinate *> coordsPlaced;


public:
    Board();
    ~Board();
    void printBoard();
    void resizeBoard(int row, int col);
    bool placeTile(char row, int col, Tile * tile);
    Tile* getTile(int row, int col);
    int getHorizontalSize();
    int getVerticalSize();

    void getBoard(int row, int col);
    void setBoard(int row, int col);

    bool checkRowTiles(Tile* current, Tile* left, Tile* right);
    bool checkColTiles(Tile* current, Tile* above, Tile* below);
    bool duplicate(Tile* tile, int row, int col);

    bool checkQuirkle();
    int calculateScore();
};

#endif // BOARD_H