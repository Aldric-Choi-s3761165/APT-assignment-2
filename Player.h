#ifndef PLAYER_H
#define PLAYER_H 

#include <iostream>
#include <string>
#include "LinkedList.h"

class Player{
private:
    int id;
    std::string name;
    std::string email;
    int score;
    LinkedList* hand;

public:
    Player(int id, std::string name, std::string email);
    Player(std::string name, LinkedList* hand);
    ~Player();

    std::string getName();
    int getScore();
    LinkedList* getPlayerhand();

    void setPlayerName(std::string name);
    void setPlayerScore(int score);

    void displayTileHand();
    void clearPlayerHand();
};

#endif //  PLAYER_H