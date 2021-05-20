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
    
    bool placeTile(char row, int col, Tile * tile, bool loadSave);
    void setBoard(int row, int col);

    bool checkQuirkle();
    int calculateScore();

    int getHorizontalSize();
    int getVerticalSize();

    LinkedList* getAllTiles();

private:
    Tile* getTile(int row, int col);

    // methods for checking if tile placement is valid
    bool checkRowTiles(Tile* current, Tile* left, Tile* right, bool dontPrint);
    bool checkColTiles(Tile* current, Tile* above, Tile* below, bool dontPrint);
    bool duplicate(Tile* tile, int row, int col);

    // checking for quirkle as well as used for calculating scores
    int checkQuirkleVertical();
    int checkQuirkleHorizontal();

    void errors(int error, bool dontPrint);
    
    std::vector<std::vector<Tile *> > vectorBoard;
    bool newGame;
    int previouslyAdded[2];
    //LinkedList* placeTileOrder;

    void resizeBoard(int row, int col);
    void addRowAbove(int row, int col);
    void addRowBelow(int row, int col);
    void addColLeft(int row, int col);
    void addColRight(int row, int col);

};

#endif // BOARD_Hh