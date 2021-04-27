#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    bag = new LinkedList();
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

void GameEngine::gameRun() {
    char colours[6] = { RED, ORANGE, GREEN, BLUE, PURPLE, YELLOW };
    int shapes[6] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            Tile* tile = new Tile(colours[i], shapes[j]);
            bag->addNode(tile);
        }
    }
    
    bag->printNodes();
}