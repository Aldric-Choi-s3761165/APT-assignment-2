#include "Coordinate.h"

Coordinate::Coordinate(int row, int col){
    this->row = row;
    this->col = col;
} 

Coordinate::~Coordinate(){

}

int Coordinate::getRow(){
    return row;
}

int Coordinate::getCol(){
    return col;
}

void Coordinate::shiftRowDown(){
        row++;
}

void Coordinate::shiftColLeft(){
    col++;
}