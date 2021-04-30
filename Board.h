#ifndef BOARD_H
#define BOARD_H 
#include "Tile.h"
#include "Coordinate.h"
#include <vector>


class Board {
private:
    int row;
    int col;
    std::vector<std::vector<Tile *>> vectorBoard;
    //std::vector<Coordinate *> coordsPlaced;


public:
    Board();
    ~Board();
    void printBoard();
    void resizeBoard(int row, int col);
    void placeTile(int row, int col, Tile * tile);
    Tile* getTile(int row, int col);
    int getHorizontalSize();
    int getVerticalSize();

    void getBoard(int row, int col);
    int setBoard(int row, int col);
};

#endif // BOARD_H