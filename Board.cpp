#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>


Board::Board(){
    vectorBoard = std::vector<std::vector<Tile *>>(6, std::vector<Tile *> (6, nullptr));
    newGame = true;
    // std::vector<Tile *> temp;
    // temp.push_back(nullptr);
    // vectorBoard.push_back(temp);
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
    
}

bool Board::checkQuirkle() {
    int check = 0;
    bool quirkleExists = false;

    // checks below
    for(int i = previouslyAdded[0]; i < getVerticalSize() && vectorBoard[i][previouslyAdded[1]] != nullptr; i++) {
        check++;
    }
    
    // checks above
    for(int i = previouslyAdded[0] - 1; i > 0 && vectorBoard[i][previouslyAdded[1]] != nullptr; i--) {
        check++;
    }

    if (check == 6) {
        quirkleExists = true;
    }

    if(quirkleExists == false) {
        check = 0;
        // checks left and right
        for(int i = previouslyAdded[1]; i < getHorizontalSize() && vectorBoard[previouslyAdded[0]][i] != nullptr; i++) {
            check++;
        }
        for(int i = previouslyAdded[1] - 1; i > 0 && vectorBoard[previouslyAdded[0]][i] != nullptr; i--) {
            check++;
        }

        if (check == 6) {
            quirkleExists = true;
        }
    }

    return quirkleExists;
}

int Board::calculateScore() {

    // col

    // int numberPlacedTile = 0;
 
    // int maxRowSize = getVerticalSize();

    // Tile *currTile = nullptr;

    // for(int currRow = 0; currRow < maxRowSize; currRow++){
    //     currTile = getTile(currRow, previouslyAdded[1]);
    //     if(emptyTileValidation(currTile)){
    //         numberPlacedTile++;
    //     }
    // }
    // return numberPlacedTile;


    // // row

    // int numberPlacedTile = 0;
 
    // int maxColSize = getHorizontalSize();

    // Tile *currTile = nullptr;

    // for(int currCol = 0; currCol < maxColSize; currCol++){
    //     currTile = getTile(previouslyAdded[0],currCol);
    //     if(emptyTileValidation(currTile)){
    //         numberPlacedTile++;
    //     }       
    // }
    // return numberPlacedTile;

    return 0;
}

bool Board::placeTile(char row, int col, Tile * tile){
    bool success = true;

    char start = 'A';
    int rowCheck = 0;

    int maxRowSize = getVerticalSize();
    int maxColSize = getHorizontalSize();

    for(int i = 0; i < maxRowSize; i++) {
        if(start != row) {
            start++;
            rowCheck++;
        }
        else {
            i = maxRowSize;
        }
    }

    if(newGame == false) {
        //Checks if in range
        if(rowCheck < maxRowSize && col < maxColSize && rowCheck >= 0 && col >= 0){
            //Check if the position is null
            if(vectorBoard[rowCheck][col] == nullptr){
                
                Tile* leftOfTile = getTile(rowCheck, col-1);
                Tile* rightOfTile = getTile(rowCheck, col+1);
                Tile* aboveOfTile = getTile(rowCheck-1, col);
                Tile* belowOfTile = getTile(rowCheck+1, col);

                // Check whether beside the position has a tile
                if(leftOfTile == nullptr && aboveOfTile == nullptr && rightOfTile == nullptr && belowOfTile == nullptr){
                    std::cout << "INVALID: There is no tile beside the position you are placing." << std::endl;
                    success = false;
                }
                else{
                    if(leftOfTile != nullptr || rightOfTile != nullptr) {
                        success = checkRowTiles(tile, leftOfTile, rightOfTile);
                    }
                    
                    if(aboveOfTile != nullptr || belowOfTile != nullptr) {
                        success = checkColTiles(tile, aboveOfTile, belowOfTile);
                    }
                }
            }
            else{
                std::cout << "INVALID: Position already has a tile." << std::endl;
                success = false;
            }
        }
        else{
            std::cout << "INVALID: Position out of Bound." << std::endl;
            success = false;
        }
    }
    
    if(rowCheck < maxRowSize && col < maxColSize && rowCheck >= 0 && col >= 0 && success == true){
        if( (rowCheck == 0 && (col == 0 || col == maxColSize -1)) || (rowCheck == maxColSize && (col == 0 || col == maxColSize -1)) ) {
            std::cout << "INVALID: Cannot put in the edges of the board." << std::endl;
            success = false;
        }
        else if(vectorBoard[rowCheck][col] == nullptr){
            // check duplicate in row and cols
            tile->setRowCol(rowCheck, col);
            success = duplicate(tile, rowCheck, col);

            if(success == true) {
                // coordPlaced.push_back(new Coordinate(rowCheck, col));
                vectorBoard[rowCheck][col] = tile;
                // set the previous added so it can check the score for the player
                previouslyAdded[0] = rowCheck;
                previouslyAdded[1] = col;
                //Checks if the tile placed is at the end of one of the sides of the board and resizes accordingly.
                resizeBoard(rowCheck, col);
            }
            else {
                std::cout << "Cannot have duplicate tile in the same lines." << std::endl;
                tile->setRowCol(-1, -1);
            }
            
        }
        else {
            std::cout << "Must place tile on an empty position." << std::endl;
            success = false;
        }
    }

    if(success == true) {
        // check score etc
    }

    if(success == true && newGame == true) {
        newGame = false;
    }

    return success;
}

bool Board::duplicate(Tile* tile, int row, int col) {
    std::cout << "Duplicate Method" << std::endl;
    bool noDuplicates = true;
    Tile* tiles[6];
    int tilesCounter = 0;

    // checks right
    for(int i = tile->getCol() + 1; i < getVerticalSize() && vectorBoard[tile->getRow()][i] != nullptr; i++) {
        if(tilesCounter < 6) {
            tiles[tilesCounter] = vectorBoard[tile->getRow()][i];
        }
        tilesCounter++;
    }
    
    // checks left
    for(int i = tile->getCol() - 1; i > 0 && vectorBoard[tile->getRow()][i] != nullptr; i--) {
        if(tilesCounter < 6) {
            tiles[tilesCounter] = vectorBoard[tile->getRow()][i];
        }
        tilesCounter++;
    }
    
    if(tilesCounter < 6) {
        for(int x = 0; x < tilesCounter; x++) {
            if(tile->getShape() == tiles[x]->getShape()) {
                noDuplicates = false;
                std::cout << "2" << std::endl;
            }
        }
    }
    else {
        noDuplicates = false;
    }
    
    if(noDuplicates == true) {
        for(int i = 0; i < tilesCounter; i++) {
            tiles[i] = nullptr;
        }
        tilesCounter = 0;

        // below
        for(int i = tile->getRow() + 1; i < getHorizontalSize() && vectorBoard[i][tile->getCol()] != nullptr; i++) {
            if(tilesCounter < 6){
                tiles[tilesCounter] = vectorBoard[i][tile->getCol()];
            }
            tilesCounter++;
        }

        // above
        for(int i = tile->getRow() - 1; i > 0 && vectorBoard[i][tile->getCol()] != nullptr; i--) {
            if(tilesCounter < 6){
                tiles[tilesCounter] = vectorBoard[i][tile->getCol()];
            }
            tilesCounter++;
        }

        if(tilesCounter < 6) {
            for(int x = 0; x < tilesCounter; x++) {
                if(tile->getColour() == tiles[x]->getColour()) {
                    std::cout << "3" << std::endl;
                    noDuplicates = false;
                }
            }
        }
        else {
            noDuplicates = false;
        }
        
    }

    return noDuplicates;
}

bool Board::checkRowTiles(Tile* current, Tile* left, Tile* right) {
    bool returnVal = true;

    if(left != nullptr) {
        if(current->getColour() != left->getColour() || current->getShape() == left->getShape()) {
            std::cout << "INVALID: It should be the same colour and not the same shape." << std::endl;
            returnVal = false;
        }
    }

    if(right != nullptr) {
        if(current->getColour() != right->getColour() || current->getShape() == right->getShape()) {
            std::cout << "INVALID: It should be the same colour and not the same shape." << std::endl;
            returnVal = false;
        }
    }

    return returnVal;
}

bool Board::checkColTiles(Tile* current, Tile* above, Tile* below) {
    bool returnVal = true;
    
    if(above != nullptr){
        if(current->getShape() != above->getShape() || current->getColour() == above->getColour()){
            std::cout << "INVALID: It should be the same shape and not the same colour." << std::endl;
            returnVal = false;
        }
    }

    if(below != nullptr){
        if(current->getShape() != below->getShape() || current->getColour() == below->getColour()){
            std::cout << "INVALID: It should be the same shape and not the same colour." << std::endl;
            returnVal = false;
        }
    }

    return returnVal;
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
    if(row == minRowSize && maxRowSize < MAX_BOARD_DIMENSION){
        std::vector<Tile *> temp;

        // adds a new row at the top
        for(int i = 0; i < maxColSize + 1; i++){
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);

        //shift all down by 1
        std::rotate(vectorBoard.rbegin(), vectorBoard.rbegin() + 1, vectorBoard.rend());

        for (row = minRowSize; row != maxRowSize; row++) {
            for (col = minColSize; col != maxColSize; col++) {
                if(vectorBoard[row][col] != nullptr) {
                    vectorBoard[row][col]->shiftRowDown();
                    vectorBoard[row][col]->setRowCol(row+1, col);
                }
            }
        }
        previouslyAdded[0] += 1;

    }
    
    // if tile is added at the bottom
    else if(row == maxRowSize && maxRowSize < MAX_BOARD_DIMENSION) {
        std::vector<Tile *> temp;
        
        // adds a new row at the bottom
        for (int i = 0; i < maxColSize + 1; i++) {
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);
    }

    // if tile is added at the left
    else if(col == minColSize && maxColSize < MAX_BOARD_DIMENSION) {

        // add a col with nullptr each row at the front
        // move all tiles by one position to the left
        for(auto &row : vectorBoard){
            row.push_back(nullptr);
            std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
        }

        for (row = minRowSize; row != maxRowSize; row++) {
            for (col = minColSize; col != maxColSize; col++) {
                if(vectorBoard[row][col] != nullptr) {
                    vectorBoard[row][col]->shiftColRight();
                    vectorBoard[row][col]->setRowCol(row, col+1);
                }
            }
        }
        previouslyAdded[1] += 1;
    }

    //if tile is added to the right
    else if(col == maxColSize && maxColSize < MAX_BOARD_DIMENSION) {

        // add a col with nullptr each row at the last
        for(auto &row : vectorBoard){
            row.push_back(nullptr);
        }
    }
}

int Board::getHorizontalSize(){
    return vectorBoard[0].size();
}

int Board::getVerticalSize(){
    return vectorBoard.size();
}

void Board::setBoard(int row, int col) {
    vectorBoard = std::vector<std::vector<Tile *>>(row, std::vector<Tile *> (col, nullptr));
}