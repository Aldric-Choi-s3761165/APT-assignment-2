#include "Tile.h"

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
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

int Tile::getCol() {
    return this->col;
}

int Tile::getRow() {
    return this->row;
}