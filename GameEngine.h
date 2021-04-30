#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "LinkedList.h"
#include "Player.h"
#include "Types.h"
#include "Tile.h"
#include "Board.h"
#include <memory>

class GameEngine{

public:
    GameEngine();
    ~GameEngine();
    bool newPlayer(int id, std::string n);
    bool existingPlayer(std::string n, int s, std::string h);
    void existingBoard(int row, int col, std::string states);
    void gameRun(int id);
    void setupGame();
    void testing();

private:
    
    Player* players[TOTAL_PLAYERS];
    std::unique_ptr<LinkedList> bag;
    std::unique_ptr<Board> board;
    
};


#endif // GAMEENGINE_H