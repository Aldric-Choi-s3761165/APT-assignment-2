#ifndef PLAYER_H
#define PLAYER_H 

#include <iostream>
#include <string>
#include <memory>
#include "LinkedList.h"

class Player{
public:
    Player(int id, std::string name);
    Player(int id, std::string name, std::unique_ptr<LinkedList> hand, int score);
    ~Player();

    std::string getName();
    int getScore();
    std::unique_ptr<LinkedList> getPlayerhand();

    void setPlayerScore(int score);

    void displayTileHand();
    void clearPlayerHand();

    void addNode(Tile* t);

private:
    int id;
    std::string name;
    int score;
    //LinkedList* hand;
    std::unique_ptr<LinkedList> hand;

};

#endif // PLAYER_H