#ifndef TILE_H
#define TILE_H

#include "Types.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour colour,Shape shape);
   ~Tile();

   char getColour();
   int getShape();
private:
   Colour colour;
   Shape  shape;
};

#endif // TILE_H
