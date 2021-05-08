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

   Colour getColour();
   Shape getShape();

   int getRow();
   int getCol();
   Colour getCharColour(int row);
   
   void setRowCol(int row, int col);
   void shiftRowDown();
   void shiftColRight();

private:
   Colour colour;
   Shape  shape;
   int row;
   int col;
};

#endif // TILE_H
