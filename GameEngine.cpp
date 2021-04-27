#include "GameEngine.h"
#include <iostream>
#include <random>

GameEngine::GameEngine() {
    bag = new LinkedList();
}

GameEngine::~GameEngine() {
    bag = nullptr;
}

bool GameEngine::newPlayer(int id, std::string n) {
    Player* player = new Player(id, "test");
    players[id - 1] = player;
    LinkedList* playerHand = new LinkedList();

    for(int i = 0; i < PLAYER_HAND_LIMIT; i++) {
        Tile* t = bag->pop();
        if(t != nullptr) {
            playerHand->addNode(t);
        }
        else {
            throw std::runtime_error("Bag is empty, error has occured");
        }
    }

    playerHands[id - 1] = playerHand;

    return true;
}

bool GameEngine::existingPlayer(std::string n, int s, std::string h) {
    return true;
}

void GameEngine::createBoard(int row, int col, std::string states) {

}

void GameEngine::gameRun(int id) {
    
}

void GameEngine::setupGame() {
    char colours[6] = { RED, ORANGE, GREEN, BLUE, PURPLE, YELLOW };
    int shapes[6] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };
    
    std::random_device generator;
    std::uniform_int_distribution<int> distribute(0, BAG_MAX_LIMIT);
    Tile* tempArray[BAG_MAX_LIMIT];
    int counter = 0;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            for(int x = 0; x < 3; x++) {
                Tile* tile = new Tile(colours[i], shapes[j]);
                tempArray[counter] = tile;
                counter++;
            }
        }
    }

    for(int i = 0; i < BAG_MAX_LIMIT; i++) {
        bool check = false;
        while(check == false) {
            int num = distribute(generator);
            if(tempArray[num] != nullptr) {
                bag->addNode(tempArray[num]);
                tempArray[num] = nullptr;
                check = true;
            }
        }
    }


    // testing bag printing for comparisson with testing method
    std::cout << "Current Bag: " << std::endl;
    bag->printNodes();
    std::cout << std:: endl;
    
}

void GameEngine::testing() {
    for(int x = 0; x < 2; x++) {
        std::cout << "Player Hand: " << x << std::endl;
        playerHands[x]->printNodes();
        std::cout << std::endl;
    }

    std::cout << "Current Bag: " << std::endl;
    bag->printNodes();
}