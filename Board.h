#ifndef BOARD_H
#define BOARD_H 
#include "Tile.h"
#include <vector>
#include "LinkedList.h"

class Board {

public:
    Board();
    ~Board();

    void printBoard();
    
    bool placeTile(char row, int col, Tile * tile);
    void setBoard(int row, int col);

    bool checkQuirkle();
    int calculateScore();

    int getHorizontalSize();
    int getVerticalSize();

    LinkedList* getPlaceTileOrder();

private:
    void resizeBoard(int row, int col);
    Tile* getTile(int row, int col);

    // methods for checking if tile placement is valid
    bool checkRowTiles(Tile* current, Tile* left, Tile* right);
    bool checkColTiles(Tile* current, Tile* above, Tile* below);
    bool duplicate(Tile* tile, int row, int col);

    // checking for quirkle as well as used for calculating scores
    int checkQuirkleVertical();
    int checkQuirkleHorizontal();
    
    std::vector<std::vector<Tile *>> vectorBoard;
    bool newGame;
    int previouslyAdded[2];
    LinkedList* placeTileOrder;
    // std:vector<Coordinate *> coordsPlaced;

};

#endif // BOARD_Hh