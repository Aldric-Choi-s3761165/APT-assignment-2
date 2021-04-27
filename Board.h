#ifndef BOARD_H
#define BOARD_H 

class Board {
private:
    int row;
    int col;
    char board[];

public:
    void getRow();
    void getCol();
    void getBoard(int row, int col);

    int setRow();
    int setCol();
    int setBoard(int row, int col);
};

#endif // BOARD_H