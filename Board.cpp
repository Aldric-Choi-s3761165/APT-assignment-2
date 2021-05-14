#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>



Board::Board(){
    vectorBoard = std::vector<std::vector<Tile *>>(INITIAL_BOARD_SIZE, std::vector<Tile *> (INITIAL_BOARD_SIZE, nullptr));
    newGame = true;
}

Board::~Board(){
    for(int x = 0; x < getVerticalSize(); x++) {
        for(int y = 0; y < getHorizontalSize(); y++) {
            if(vectorBoard[x][y] != nullptr) {
                delete vectorBoard[x][y];
            }
        }
    }
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
                // place the tile on the board
                Tile *currTile = vectorBoard[i][j];
                // print out the tile
                std::cout << currTile->getColour() << currTile->getShape();
            }
            if (j == maxCol-1) {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
    }
    
}

int Board::checkQuirkleVertical() {
    int check = 0;

    for(int i = previouslyAdded[0]; i < getVerticalSize() && vectorBoard[i][previouslyAdded[1]] != nullptr; i++) {
        check++;
    }
    for(int i = previouslyAdded[0] - 1; i > 0 && vectorBoard[i][previouslyAdded[1]] != nullptr; i--) {
        check++;
    }

    return check;
}

int Board::checkQuirkleHorizontal() {
    int check = 0;

    for(int i = previouslyAdded[1]; i < getHorizontalSize() && vectorBoard[previouslyAdded[0]][i] != nullptr; i++) {
        check++;
    }
    for(int i = previouslyAdded[1] - 1; i > 0 && vectorBoard[previouslyAdded[0]][i] != nullptr; i--) {
        check++;
    }

    return check;
}



bool Board::checkQuirkle() {
    int check = 0;
    bool quirkleExists = false;

    // checks above and below
    check = checkQuirkleVertical();

    if (check == 6) {
        quirkleExists = true;
    }

    if(quirkleExists == false) {
        check = 0;
        
        // checks left and right
        check = checkQuirkleHorizontal();

        if (check == 6) {
            quirkleExists = true;
        }
    }

    return quirkleExists;
}

int Board::calculateScore() {

    int vertical = checkQuirkleVertical();
    int horizontal = checkQuirkleHorizontal();
    int bonus = 0;
    int returnValue;
    int const Qwirkle = 6;

    if(vertical == Qwirkle) {
        bonus += 6;
    }
    
    if(horizontal == Qwirkle) {
        bonus += 6;
    }

    returnValue = vertical + horizontal + bonus;

    if(vertical == 1 || horizontal == 1) {
        returnValue--;
    }

    return returnValue;
}

bool Board::placeTile(char row, int col, Tile * tile, bool loadSave){
    
    bool success = true;

    char start = 'A';
    int rowCheck = 0;

    int maxRowSize = getVerticalSize();
    int maxColSize = getHorizontalSize();

    //Changes the char row into an int so the board will know the size
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
                    errors(1, loadSave);
                    success = false;
                }
                else{
                    // Check the tiles of the line
                    if(leftOfTile != nullptr || rightOfTile != nullptr) {
                        success = checkRowTiles(tile, leftOfTile, rightOfTile, loadSave);
                    }
                    
                    // Check the tiles of the line
                    if(aboveOfTile != nullptr || belowOfTile != nullptr) {
                        success = checkColTiles(tile, aboveOfTile, belowOfTile, loadSave);
                    }
                }
            }
            else {
                errors(2, loadSave);
                success = false;
            }
        }
        else{
            errors(3, loadSave);
            success = false;
        }
    }
    
    
    if(success == true){
        if(!(rowCheck < maxRowSize && col < maxColSize && rowCheck >= 0 && col >= 0)) {
            errors(3, loadSave);
            success = false;
        }
        else if( ((rowCheck == 0 && (col == 0 || col == maxColSize -1)) || 
            (rowCheck == maxRowSize - 1  && (col == 0 || col == maxColSize -1)))
            && newGame == true ) {
            errors(4, loadSave);
            success = false;
        }
        else if(vectorBoard[rowCheck][col] == nullptr){
            // check duplicate in row and cols
            tile->setRowCol(rowCheck, col);
            success = duplicate(tile, rowCheck, col);

            if(success == true) {
                vectorBoard[rowCheck][col] = tile;
                // set the previous added so it can check the score for the player
                previouslyAdded[0] = rowCheck;
                previouslyAdded[1] = col;

                //Checks if the tile placed is at the end of one of the sides of the board and resizes accordingly.

                if(loadSave == false) {
                    resizeBoard(rowCheck, col);
                }
                
            }
            else {
                errors(5, loadSave);
                tile->setRowCol(-1, -1);
            }
            
        }
        else {
            errors(6, loadSave);
            success = false;
        }
    }

    if(success == true && newGame == true) {
        newGame = false;
    }

    return success;
}

bool Board::duplicate(Tile* tile, int row, int col) {
    bool noDuplicates = true;
    Tile* tiles[6];
    int tilesCounter = 0;

    // checks tiles to the right of the current tile
    for(int i = tile->getCol() + 1; i < getVerticalSize() && vectorBoard[tile->getRow()][i] != nullptr; i++) {
        if(tilesCounter < 6) {
            tiles[tilesCounter] = vectorBoard[tile->getRow()][i];
        }
        tilesCounter++;
    }
    
    // checks tiles to the left of the current tile
    for(int i = tile->getCol() - 1; i > 0 && vectorBoard[tile->getRow()][i] != nullptr; i--) {
        if(tilesCounter < 6) {
            tiles[tilesCounter] = vectorBoard[tile->getRow()][i];
        }
        tilesCounter++;
    }

    // Checks whether if the line has already 6 tiles
    if(tilesCounter < 6) {
        for(int x = 0; x < tilesCounter; x++) {
            if(tile->getShape() == tiles[x]->getShape()) {
                noDuplicates = false;
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

        // checks tiles below the current tile
        for(int i = tile->getRow() + 1; i < getHorizontalSize() && vectorBoard[i][tile->getCol()] != nullptr; i++) {
            if(tilesCounter < 6){
                tiles[tilesCounter] = vectorBoard[i][tile->getCol()];
            }
            tilesCounter++;
        }

        // checks tiles above the current tile
        for(int i = tile->getRow() - 1; i > 0 && vectorBoard[i][tile->getCol()] != nullptr; i--) {
            if(tilesCounter < 6){
                tiles[tilesCounter] = vectorBoard[i][tile->getCol()];
            }
            tilesCounter++;
        }

        // Checks whether if the line has already 6 tiles
        if(tilesCounter < 6) {
            for(int x = 0; x < tilesCounter; x++) {
                if(tile->getColour() == tiles[x]->getColour()) {
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

bool Board::checkRowTiles(Tile* current, Tile* left, Tile* right, bool dontPrint) {
    bool returnVal = true;

    if(left != nullptr) {
        if(current->getColour() != left->getColour() || current->getShape() == left->getShape()) {
            errors(7, dontPrint);
            returnVal = false;
        }
    }

    if(right != nullptr) {
        if(current->getColour() != right->getColour() || current->getShape() == right->getShape()) {
            errors(7, dontPrint);
            returnVal = false;
        }
    }

    return returnVal;
}

bool Board::checkColTiles(Tile* current, Tile* above, Tile* below, bool dontPrint) {
    bool returnVal = true;
    
    if(above != nullptr){
        if(current->getShape() != above->getShape() || current->getColour() == above->getColour()){
            errors(8, dontPrint);
            returnVal = false;
        }
    }

    if(below != nullptr){
        if(current->getShape() != below->getShape() || current->getColour() == below->getColour()){
            errors(8, dontPrint);
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
    int maxRowSize = getVerticalSize() - 1;
    int maxColSize = getHorizontalSize() - 1;

    // if tile is added at the top
    if(row == minRowSize && maxRowSize < MAX_BOARD_DIMENSION - 1){
        std::vector<Tile *> temp;

        // adds a new row at the top
        for(int i = 0; i < maxColSize + 1; i++){
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);

        //shift all down by 1
        std::rotate(vectorBoard.rbegin(), vectorBoard.rbegin() + 1, vectorBoard.rend());

        for (row = minRowSize; row != maxRowSize + 1; row++) {
            for (col = minColSize; col != maxColSize + 1; col++) {
                if(vectorBoard[row][col] != nullptr) {
                    vectorBoard[row][col]->shiftRowDown();
                }
            }
        }
        previouslyAdded[0] += 1;

    }
    
    // if tile is added at the bottom
    else if(row == maxRowSize && maxRowSize < MAX_BOARD_DIMENSION - 1) {
        std::vector<Tile *> temp;
        
        // adds a new row at the bottom
        for (int i = 0; i < maxColSize + 1; i++) {
            temp.push_back(nullptr);
        }
        vectorBoard.push_back(temp);
    }

    // if tile is added at the left
    else if(col == minColSize && maxColSize < MAX_BOARD_DIMENSION - 1) {

        // add a col with nullptr each row at the front
        // move all tiles by one position to the left
        for(auto &row : vectorBoard){
            row.push_back(nullptr);
            std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
        }

        for (row = minRowSize; row != maxRowSize + 1; row++) {
            for (col = minColSize; col != maxColSize + 1; col++) {
                if(vectorBoard[row][col] != nullptr) {
                    vectorBoard[row][col]->shiftColRight();
                }
            }
        }
        previouslyAdded[1] += 1;
    }

    //if tile is added to the right
    else if(col == maxColSize && maxColSize < MAX_BOARD_DIMENSION - 1) {

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

LinkedList* Board::getAllTiles(){
    LinkedList* allTiles = new LinkedList();

    for(int x = 0; x < getHorizontalSize(); x++) {
        for(int y = 0; y < getVerticalSize(); y++) {
            if(vectorBoard[x][y] != nullptr) {
                Tile* t = new Tile(vectorBoard[x][y]->getColour(), vectorBoard[x][y]->getShape());
                t->setRowCol(vectorBoard[x][y]->getRow(), vectorBoard[x][y]->getCol());
                allTiles->addBack(t);
            }
        }
    }

    return allTiles;
}

void Board::errors(int error, bool dontPrint) {
    if(dontPrint == false) {
        if(error == 1) {
            std::cout << "INVALID: There is no tile beside the position you are placing." << std::endl;
        }
        else if(error == 2) {
            std::cout << "INVALID: Position already has a tile." << std::endl;
        }
        else if(error == 3) {
            std::cout << "INVALID: Position out of Bound." << std::endl;
        }
        else if(error == 4) {
            std::cout << "INVALID: Cannot place in edge during start of game." << std::endl;
        }
        else if(error == 5) {
            std::cout << "Cannot have duplicate tile in the same lines." << std::endl;
        }
        else if(error == 6) {
            std::cout << "Must place tile on an empty position." << std::endl;
        }
        else if(error == 7) {
            std::cout << "INVALID: It should be the same colour and not the same shape." << std::endl;
        }
        else if(error == 8) {
            std::cout << "INVALID: It should be the same shape and not the same colour." << std::endl;
        }
    }
}