#include "Player.h"
#include <iostream>

Player::Player(int id, std::string name) {
    this->id = id;
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}

Player::Player(int id, std::string name, int score, LinkedList* hand) {
    this->id = id;
    this->name = name;
    this->score = score;
    this->hand = hand;
}

Player::~Player() {
    delete hand;
}

std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

LinkedList* Player::getPlayerHand() {
    return hand; // only shallow copy
}

void Player::setPlayerScore(int score) {
    this->score = score;
}

void Player::displayTileHand() {
    hand->printNodes();
}

void Player::clearPlayerHand() {
    hand->removeAllNodes();
    hand = nullptr;
    
}

void Player::addNode(Tile* t) {
    this->hand->addNode(t);
}