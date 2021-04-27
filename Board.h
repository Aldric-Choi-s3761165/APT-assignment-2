#ifndef BOARD_H
#define BOARD_H 
#include "Tile.h"
#include <vector>


class Board {
private:
    int row;
    int col;
    std::vector<std::vector<Tile *>> vectorBoard;

public:
    Board();
    ~Board();
    void printBoard();
    int getHorizontalSize();
    int getVerticalSize();

    void getRow();
    void getCol();
    void getBoard(int row, int col);

    int setRow();
    int setCol();
    int setBoard(int row, int col);
};

#endif // BOARD_H