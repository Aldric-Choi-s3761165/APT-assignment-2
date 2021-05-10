#ifndef PLAYER_H
#define PLAYER_H 

#include <iostream>
#include <string>
#include "LinkedList.h"

class Player{
public:
    Player(int id, std::string name);
    Player(int id, std::string name, int score, LinkedList* hand);
    ~Player();

    int getID();
    std::string getName();
    int getScore();
    LinkedList* getPlayerHand();

    void setScore(int score);

    void displayTileHand();
    void clearPlayerHand();

    void addNode(Tile* t);

    void setSkip(bool skip);
    bool getSkip();

private:
    int id;
    std::string name;
    int score;
    LinkedList* hand;
    bool skip;

};

#endif // PLAYER_H