#include "GameEngine.h"
#include <iostream>
#include <random>

GameEngine::GameEngine() {
    bag = new LinkedList();
    board = new Board();
}

GameEngine::~GameEngine() {
    bag = nullptr;
}

// precondition; id is valid above 0 and hasn't already been added
// hence if we add player of id 1 and we create a second new player of
// id 1 again, this will replace the first created player
// However, the bag state will decrease further and the tiles that the
// first player held will be lost

bool GameEngine::newPlayer(int id, std::string n) {
    Player* player = new Player(id, n);

    for(int i = 0; i < PLAYER_HAND_LIMIT; i++) {
        Tile* t = bag->pop();
        if(t != nullptr) {
            player->addNode(t);
        }
        else {
            throw std::runtime_error("Bag is empty, error has occured"); //temp testing may remove later
        }
    }

    players[id - 1] = player;

    return true;
}

bool GameEngine::existingPlayer(int id, std::string name, int score, LinkedList* hand) {
    Player* player = new Player(id, name, score, hand);
    
    players[id - 1] = player;
    
    return true;
}

void GameEngine::createBoard(int row, int col, std::string states) {
    board->setBoard(row, col);
    // setup states
}

void GameEngine::gameRun(int id) {
    bool gameRun = true;
    std::string input;
    
    while(gameRun) {
        display(id);
        std::cin >> input;
        getAction(input, id);
        
        // game logic
        // check if winner
    }

    players[1]->getPlayerHand()->removeNode(RED, CIRCLE);
    players[1]->displayTileHand();
}

void GameEngine::getAction(std::string line, int id){
    if(line.size() == 14) {
        // place action
        Tile* t = players[id]->getPlayerHand()->removeNode(line[7], line[8]);
        if(t != nullptr) {
            board->placeTile(line[13], line[14], t);
            players[id]->addNode(bag->pop());
        }
        else {
            std::cout << "Tile does not exist in your hand" << std::endl;
        }
    }
    else if(line.size() == 10) {
        // replace action
        Tile* t = players[id]->getPlayerHand()->removeNode(line[9], line[10]);
        if(t != nullptr) {
            bag->addBack(t);
            players[id]->addNode(bag->pop());
        }
        else {
            std::cout << "Tile does not exist in your hand" << std::endl;
        }
    }
}

void GameEngine::display(int id) {
    Player* currPlayer = players[id - 1];

    std::cout << currPlayer->getName() << ", it's your turn" << std::endl;
    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        Player* player = players[i];
        std::cout << "Score for " << player->getName() << ": " << players[i]->getScore() << std::endl;
    }

    board->printBoard();

    std::cout << std::endl;
    std::cout << "Your hand is" << std::endl;
    currPlayer->displayTileHand();
    std::cout << std::endl;
}

void GameEngine::setupGame() {
    char colours[6] = { RED, ORANGE, GREEN, BLUE, PURPLE, YELLOW };
    int shapes[6] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };
    
    std::random_device generator;
    std::uniform_int_distribution<int> distribute(0, BAG_MAX_LIMIT - 1);
    Tile* tempArray[BAG_MAX_LIMIT];
    int counter = 0;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            for(int x = 0; x < 2; x++) {
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

}

void GameEngine::testing() {
    
    // testing board in game engine
    board->printBoard();
    Tile * firstTile = bag->pop();
    board->placeTile(5, 3, firstTile);
    board->printBoard();
    Tile * secondTile = bag->pop();
    board->placeTile(3, 5, secondTile);
    board->printBoard();    
    Tile * thirdTile = bag->pop();
    board->placeTile(0, 2, thirdTile);
    board->printBoard();
    Tile * fourthTile = bag->pop();
    board->placeTile(2, 0, fourthTile);
    board->printBoard();

    // testing bag printing for comparisson with testing method
    std::cout << "Current Bag: " << std::endl;
    bag->printNodes();
    std::cout << std:: endl;
    
    for(int x = 1; x <= 2; x++) {
        std::cout << "Player Hand: " << x << std::endl;
        players[x - 1]->displayTileHand();
        std::cout << std::endl;
    }

    std::cout << "Current Bag: " << std::endl;
    bag->printNodes();
}