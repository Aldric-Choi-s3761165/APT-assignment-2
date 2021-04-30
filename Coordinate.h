#ifndef COORDINATE_H
#define COORDINATE_H 
#include <vector>

class Coordinate {
private:
    int row;
    int col;

public:
    Coordinate(int row, int col);
    ~Coordinate();
    int getRow();
    int getCol();

    void shiftRowDown();
    void shiftColLeft();
};
#endif // BOARD_H