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
    int getPlayerId(std::string name);
    void newBag(LinkedList* bag);

private:
    void display(int id);
    bool getAction(std::string line, int id);
    void errors(int error);
    void gameResult();
    void addScore(int id,int score);
    int calculateScore(int row,int col);
    void checkScore(int id, char y, int x);
    
    LinkedList* bag;
    Player* players[TOTAL_PLAYERS];
    Board* board;
    bool gameRunning;
    
};


#endif // GAMEENGINE_H