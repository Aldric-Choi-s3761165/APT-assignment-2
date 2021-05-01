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
    void getAction(std::string line, int id);

private:
    LinkedList* bag;
    Player* players[TOTAL_PLAYERS];
    Board* board;
    
};


#endif // GAMEENGINE_H