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