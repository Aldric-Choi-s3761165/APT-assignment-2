#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "LinkedList.h"
#include "Player.h"
#include "Types.h"
#include "Tile.h"
#include "Board.h"

class GameEngine{

public:
    GameEngine();
    ~GameEngine();
    bool newPlayer(int id, std::string n);
    bool existingPlayer(int id, std::string name, int score, LinkedList* hand);
    void createBoard(int row, int col, std::string states);
    void gameRun(int id);
    void setupGame();
    void testing();
    void display(int id);
    bool getAction(std::string line, int id);
    void errors(int error);

    void gameResult(int id1, int id2);
    void addScore(int id,int score);
    int calculateScore(int row,int col);
    int choosingWinner(int id1, int id2); 
private:
    LinkedList* bag;
    Player* players[TOTAL_PLAYERS];
    Board* board;
    
};


#endif // GAMEENGINE_H