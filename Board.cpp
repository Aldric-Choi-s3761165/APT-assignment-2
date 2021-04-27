#include "Board.h"
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;


Board::Board(){
    
}

Board::~Board(){

}

void Board::printBoard(){
    char rowLabel = 'A';
    // int maxRow = getVerticalSize();
    // int maxCol = getHorizontalSize();
    int maxRow = 6;
    int maxCol = 6;
    std::string line = "  -";
    std::string num = "   ";
    std::vector<std::vector<Tile *>> vectorBoard (maxRow, std::vector<Tile*> (maxCol, nullptr));

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
            std::cout << "| ";
            if(vectorBoard[i][j]== nullptr){
                std::cout << " ";
            } 
            else{
                //print out the tile
            }
            if (j == maxCol-1) {
                std::cout << '|';
            }
        }
        cout<< endl;
    }
}

int Board::getHorizontalSize(){
    return vectorBoard[0].size();
}

int Board::getVerticalSize(){
    return vectorBoard.size();
}