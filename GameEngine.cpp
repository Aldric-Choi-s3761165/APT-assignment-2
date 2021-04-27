#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    
}

GameEngine::~GameEngine() {
    bag = nullptr;
}

bool GameEngine::newPlayer(int id, std::string n) {
    Player* pla = new Player(id, "test");
    players[id - 1] = pla;
    return true;
}

bool GameEngine::existingPlayer(std::string n, int s, std::string h) {
    return true;
}

void GameEngine::createBoard(int row, int col, std::string states) {

}

void GameEngine::gameRun(std::string currentPlayer) {

}