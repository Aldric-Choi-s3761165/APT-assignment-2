#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>


Board::Board(){
    // The initialises the size of the board to 6x6
    vectorBoard = std::vector<std::vector<Tile *>>(6, std::vector<Tile *> (6, nullptr));
}

Board::~Board(){

}

void Board::printBoard(){
    char rowLabel = 'A';
    int maxRow = getVerticalSize();
    int maxCol = getHorizontalSize();
    std::string line = "  -";
    std::string num = "   ";

    for(int i = 0; i < maxCol; i++){
        if(i > 9){
            num += std::to_string(i) + " ";
        }
        else {
            num += std::to_string(i) + "  ";
        }
        line += "---";
    }

    std::cout << num << std::endl;
    std::cout << line << std::endl;

    for(int i = 0; i < maxRow; i++) {
        std::string rowString;
        std::cout << rowLabel++ << " ";

        for(int j = 0; j < maxCol; j++) {
            std::cout << "|";
            if(vectorBoard[i][j]== nullptr){
                std::cout << "  ";
            } 
            else{
                //print out the tile
                Tile *currTile = vectorBoard[i][j];
                std::cout << currTile->getColour() << currTile->getShape();
            }
            if (j == maxCol-1) {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
    }

    //Checks if stored correctly
    for(auto &coord : coordsPlaced){
        Tile * currTile = getTile(coord->getRow(), coord->getCol());
        std::cout << "Tile: " << currTile->getColour() << currTile->getShape() << " Row: " << coord->getRow() << " Col: " << coord->getCol() << std::endl;
    }
}

void Board::placeTile(int row, int col, Tile * tile){
    int maxRowSize = getVerticalSize();
    int maxColSize = getHorizontalSize();
    if(row < maxRowSize && col < maxColSize && row >= 0 && col >= 0){
        if(vectorBoard[row][col] == nullptr){
            //coordsPlaced.push_back(new Coordinate(row, col));
            tile->setRowCol(row, col);
            vectorBoard[row][col] = tile;
            //Checks if the tile placed is at the end of one of the sides of the board and resizes accdgly.
            resizeBoard(row, col);
        }
    }
}

Tile* Board::getTile(int row, int col){
    int maxRowSize = getVerticalSize() - 1;
    int maxColSize = getHorizontalSize() - 1;
    Tile *tile = nullptr;
    //if within board
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0) {
        tile = vectorBoard[row][col];
    }
    return tile;
}

void Board::resizeBoard(int row, int col){
    int minRowSize = 0;
    int minColSize = 0;
    int maxRowSize = getVerticalSize()-1;
    int maxColSize = getHorizontalSize()-1;

    // if tile is added at the top
    if(row == minRowSize){
        std::vector<Tile *> temp;

        // adds a new row at the top
        for(int i = 0; i < maxColSize + 1; i++){
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);

        //shift all down by 1
        std::rotate(vectorBoard.rbegin(), vectorBoard.rbegin() + 1, vectorBoard.rend());

        // Shifts all coordinates down by one row
        for(auto &coord : coordsPlaced){
            coord->shiftRowDown();
        }
    } 
    
    // if tile is added at the bottom
    else if(row == maxRowSize) {
        std::vector<Tile *> temp;
        
        // adds a new row at the bottom
        for (int i = 0; i < maxColSize + 1; i++) {
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);
    }

    // if tile is added at the left
    else if(col == minColSize) {

        // add a col with nullptr each row at the front
        // move all tiles by one position to the left
        for(auto &row : vectorBoard){
            row.push_back(nullptr);
            std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
        }
        
        // Shifts all coordinates to the left by one col
        for(auto &coord : coordsPlaced){
            coord->shiftColLeft();
        }

        // std::vector<Tile *> temp;

        // adds a new row at the left
        // for(int i = 0; i < maxRowSize + 1; i++){
        //     temp.push_back(nullptr);
        // }
        // vectorBoard.push_back(temp);

        // // shofts all left by 1
        // std::rotate(vectorBoard.rbegin(), vectorBoard.rbegin() + 1, vectorBoard.rend());

    }

    //if tile is added to the right
    else if(col == maxColSize) {

        // add a col with nullptr each row at the last
        for(auto &row : vectorBoard){
            row.push_back(nullptr);
        }

        // std::vector<Tile *> temp;

        // // adds a new row at the right
        // for (int i = 0; i < maxRowSize + 1; i++) {
        //     temp.push_back(nullptr);
        // }
        // vectorBoard.push_back(temp);
    }
}

int Board::getHorizontalSize(){
    return vectorBoard[0].size();
}

int Board::getVerticalSize(){
    return vectorBoard.size();
}