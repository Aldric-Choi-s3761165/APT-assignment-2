#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "LinkedList.h"
#include "Player.h"
#include "Types.h"

class GameEngine{

public:
    GameEngine();
    ~GameEngine();
    bool newPlayer(int id, std::string n);
    bool existingPlayer(std::string n, int s, std::string h);
    void createBoard(int row, int col, std::string states);
    void gameRun(std::string currentPlayer);

private:
    LinkedList* bag;
    Player* players[TOTAL_PLAYERS];
    
};

#endif // GAMEENGINE_H