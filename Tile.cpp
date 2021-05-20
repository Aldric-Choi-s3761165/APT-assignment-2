#include "Tile.h"
#include <iostream>

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
    this->row = -1;
    this->col = -1;
}

Tile::~Tile(){
    // Deconstructer
}

Colour Tile::getColour() {
    return colour;
}
Shape Tile::getShape(){
    return shape;
}

int Tile::getRow(){
    return row;
}

int Tile::getCol(){
    return col;
}

Colour Tile::getCharColour(int row) {
    char letter = 'A';
    int checkRow = row;

    for(int i = 0; i < row; i++) {
        if(letter != checkRow) {
            letter++;
            checkRow++;
        }
        else {
            i = row;
        }
    }    

    return letter;
}

void Tile::setRowCol(int row, int col) {
    this->row = row;
    this->col = col;
}

void Tile::shiftRowDown() {
    row++;
}

void Tile::shiftColRight() {
    col++;
}  