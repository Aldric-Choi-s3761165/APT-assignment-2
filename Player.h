#ifndef PLAYER_H
#define PLAYER_H 

#include <iostream>
#include <string>
#include "LinkedList.h"

class Player{
public:
    Player(int id, std::string name);
    Player(int id, std::string name, LinkedList* hand, int score);
    ~Player();

    std::string getName();
    int getScore();
    LinkedList* getPlayerhand();

    void setPlayerScore(int score);

    void displayTileHand();
    void clearPlayerHand();

private:
    int id;
    std::string name;
    int score;
    LinkedList* hand;

};

#endif // PLAYER_H