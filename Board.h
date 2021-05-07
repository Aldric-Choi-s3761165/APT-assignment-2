#ifndef BOARD_H
#define BOARD_H 
#include "Tile.h"
#include <vector>


class Board {
private:
    std::vector<std::vector<Tile *>> vectorBoard;
    // std:vector<Coordinate *> coordsPlaced;


public:
    Board();
    ~Board();
    void printBoard();
    void resizeBoard(int row, int col);
    void placeTile(char row, int col, Tile * tile);
    Tile* getTile(int row, int col);
    int getHorizontalSize();
    int getVerticalSize();

    int countPlacedTileByRow(int row);
    int countPlacedTileByCol(int col);
    bool emptyTileValidation(Tile *tile);

    void getBoard(int row, int col);
    void setBoard(int row, int col);
};

#endif // BOARD_H