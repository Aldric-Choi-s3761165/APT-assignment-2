#include "Player.h"
#include <iostream>

Player::Player(int id, std::string name) {
    this->id = id;
    this->name = name;
    this->score = 0;
    //this->hand = new LinkedList;
    this->hand = std::make_unique<LinkedList>();
}

Player::Player(int id, std::string name, std::unique_ptr<LinkedList> hand, int score) {
    this->id = id;
    this->name = name;
    this->score = score;
    this->hand = std::unique_ptr<LinkedList>(new LinkedList(*hand));
}

Player::~Player() {
    //delete hand;
}

std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

std::unique_ptr<LinkedList> Player::getPlayerhand() {
    // new linkedlist with deep copy of all nodes and tiles
    std::unique_ptr<LinkedList> returnPtr = std::unique_ptr<LinkedList>(new LinkedList(*hand));
    return returnPtr; 
}

void Player::setPlayerScore(int score) {
    this->score = score;
}

void Player::displayTileHand() {
    std::cout << "Tile Hand" << std::endl;
    hand->printNodes();
}

void Player::clearPlayerHand() {
    std::cout << "Clear Hand" << std::endl;
    hand->removeAllNodes();
    hand = nullptr;
    
}

void Player::addNode(Tile* t) {
    this->hand->addNode(t);
}