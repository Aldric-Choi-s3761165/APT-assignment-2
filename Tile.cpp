#include "Tile.h"
#include "TileCodes.h"

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