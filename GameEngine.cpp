#include "GameEngine.h"
#include <iostream>
#include <random>
#include <cstring>

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
        getline(std::cin, input);
        getAction(input, id);
        
        // game logic
        // check if winner
    }

    //players[1]->getPlayerHand()->removeNode(RED, CIRCLE);
    players[1]->displayTileHand();
}

void GameEngine::getAction(std::string line, int id){

    std::string stringCheck;
    if(line.size() == 14) {
        // place action
        
        stringCheck = line.substr(0, 5);
        if(!(stringCheck.compare("place"))) {
            
            if(isalpha(line[6]) && isdigit(line[7])) {
                char colour = line[6];
                int shape = std::stoi(std::string(1,line[7]));
                Tile* t = players[id - 1]->getPlayerHand()->getNode(colour, shape);

                if(t != nullptr) {
                    if (isdigit(line[13])) {
                        char y = line[12];
                        int x = std::stoi(std::string(1,line[13]));
                        board->placeTile(y, x, t);
                        int z = t->getRow();
                        addScore(id-1,calculateScore(z,x));
                        players[id - 1]->addNode(bag->pop());
                    }
                }
                else {
                    tileDoesntExist();
                }
            }
            else 
            {
                tileDoesntExist();
            }
        }
        else{
            std::cout << "Invalid Command" << std::endl;
        }
        
    }
    else if(line.size() == 10) {
        // replace action
        
        stringCheck = line.substr(0, 7);
        if(!(stringCheck.compare("replace"))) {
            if(isalpha(line[8]) && isdigit(line[9])) {
                char colour = line[8];
                int shape = std::stoi(std::string(1,line[9]));
                Tile* t = players[id - 1]->getPlayerHand()->getNode(colour, shape);

                if(t != nullptr) {
                    bag->addBack(t);
                    players[id - 1]->addNode(bag->pop());
                }
                else {
                    tileDoesntExist();
                }
            }
            else {
                tileDoesntExist();
            }
        }
        else{
            std::cout << "Invalid Command" << std::endl;
        }
    }
}
void GameEngine:: gameResult(int id1, int id2){
    Player* Player1 = players[id1 - 1];
    Player* Player2 = players[id2 - 1];
    int winnerID = choosingWinner(id1, id2);
    Player* winnerPlayer = players[winnerID - 1];
    std::cout <<"Game over"<< std::endl;
    std::cout<<"Score for "<<Player1->getName()<<":"<<Player1->getScore()<< std::endl;
    std::cout<<"Score for "<<Player2->getName()<<":"<<Player2->getScore()<< std::endl;
    std::cout<<"Player "<<winnerPlayer->getName()<<" won!"<<std::endl;
    std::cout << std::endl;
    std::cout <<"Goodbye" <<std::endl;

}
void GameEngine::addScore(int id,int score)
{
    Player* currPlayer = players[id - 1];
    int currScore = 0;
    currScore = currPlayer->getScore() + score;
    currPlayer->setScore(currScore);
}

int GameEngine:: calculateScore(int row, int col){
    int tempScore=1;
    //minus the current tile
    tempScore+=board->countPlacedTileByCol(col)-1;
    tempScore+=board->countPlacedTileByRow(row)-1; 
    return tempScore;
}
int GameEngine:: choosingWinner(int id1, int id2){
    Player* Player1 = players[id1 - 1];
    Player* Player2 = players[id2 - 1];
    int winnerID = 0;
    if( Player1->getScore()>Player2->getScore()){
        winnerID = Player1->getID();
    }
    else if(Player2->getScore()>Player1->getScore())
    {
         winnerID = Player2->getID();
    }
    // else{
    //     return draw;
    // }
    return winnerID;
}
void GameEngine::tileDoesntExist() {
    std::cout << "Tile does not exist in your hand" << std::endl;
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