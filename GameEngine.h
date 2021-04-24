#ifndef GAMEENGINE.H
#define GAMEENGINE.H 

#include <string>
#include "LinkedList.h"
#include "Player.h"

class GameEngine{

public:
    GameEngine();
    ~GameEngine();
    bool newPlayer(std::string n);
    bool existingPlayer(std::string n, int s, std::string h);
    void createBoard(int row, int col, std::string states);
    void gameRun(std::string currentPlayer);

private:
    LinkedList* bag;
    Player* players[];
    
};

#endif //GAMEENGINE.H