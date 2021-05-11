#include "GameEngine.h"
#include <iostream>
#include <random>
#include <cstring>
#include <fstream>

GameEngine::GameEngine() {
    bag = new LinkedList();
    board = new Board();
    gameRunning = true;

    // initialize each array pos to nullptr else an error
    // will occur when getting a player if the array is uninitialized
    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        players[i] = nullptr;
    }
}

GameEngine::~GameEngine() {
    delete bag;
    delete board;
    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        if(players[i] != nullptr) {
            delete players[i];
        }
    }
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
    Colour colour = '%';
    Shape shape = -1;
    char boardRow = '%';
    int boardCol = -1;
    
    int order = 0;
    bool ready = false;
    int counter = 0;
    int rowCheck = 0;

    bool completed = false;

    // create array of tiles to be placed into the bag
    Tile* loadTiles[BAG_MAX_LIMIT];
    int loadTilesCounter = 0;

    for(int i = 0; i < BAG_MAX_LIMIT; i++) {
        loadTiles[i] = nullptr;
    }

    for (int i = 0; states[i] && int(states[i]) != ASCII_CARRIAGE; i++) {
        
        if(isupper(states[i]) && isalpha(states[i]) && states[i] != ',' && order == 0) {
            colour = states[i];
            order = 1;
        }
        else if(isdigit(states[i]) && states[i] != ',' && order == 1) {
            shape = std::stoi(std::string(1, states[i]));
            order = 2;
        }
        else if(states[i] == '@' && order == 2) {
            order = 3;
        }
        else if(isupper(states[i]) && isalpha(states[i]) && states[i] != ',' && order == 3) {
            boardRow = states[i];

            char start = 'A';
            rowCheck = 0;

            for(int i = 0; i < board->getVerticalSize(); i++) {
                if(start != boardRow) {
                    start++;
                    rowCheck++;
                }
                else {
                    i = board->getVerticalSize();
                }
            }

            order = 4;
        }
        else if(isdigit(states[i]) && states[i] != ',' && order == 4) {
            boardCol = std::stoi(std::string(1,states[i]));
            order = 5;
            ready = true;
        }
        else if(states[i] == ',' && ready == true && order == 5) {
            order = 0;
            ready = false;
            Tile* t = new Tile(colour, shape);

            t->setRowCol(rowCheck, boardCol);
            loadTiles[loadTilesCounter] = t;
            loadTilesCounter++;
        }
        else if(ready == false && order != 0) {
            throw std::runtime_error("Load game board states have been modified");
        }

        counter = i;
    }

    if(ready == true) {
        Tile* t = new Tile(colour, shape);
        t->setRowCol(rowCheck, boardCol);
        loadTiles[loadTilesCounter] = t;
        loadTilesCounter++;
    }

    // reset counter used previously for counting a stuck loop (hence, one isnt placeable)
    counter = loadTilesCounter;
    bool tilePlaced = false;
    while(completed == false) {
        int previousCounter = counter;

        for(int i = 0; i < loadTilesCounter; i++) {
            if(loadTiles[i] != nullptr) {
                int row = loadTiles[i]->getRow();
                int col = loadTiles[i]->getCol();
                if(row > 0 && row < board->getVerticalSize() && col > 0 && col < board->getHorizontalSize()) {
                    tilePlaced = board->placeTile(loadTiles[i]->getCharColour(row), loadTiles[i]->getCol(), loadTiles[i], false);
                    if(tilePlaced) {
                        loadTiles[i] = nullptr;
                        counter--;
                        tilePlaced = false;
                    }
                }
                else {
                    throw std::runtime_error("Load game board states have been modified");
                }
            }
        }

        if(previousCounter == counter) {
            throw std::runtime_error("Load game board states have been modified");
        }

        if(counter == 0) {
            completed = true;
        }
    }

}

void GameEngine::newBag(LinkedList* bag) {
    delete this->bag;
    this->bag = bag;
}

void GameEngine::gameRun(int id) {
    
    std::string input;
    
    while(gameRunning) {
        
        display(id);
        std::cout << "> ";
        getline(std::cin, input);
        
        if(std::cin) {
            // if command was completed successfully
            if(getAction(input, id)) {
                id++;
                if(id > TOTAL_PLAYERS) {
                    id = 1;
                }
            }
        }
        else {
            std::cout << "^D\n" << std::endl;
            gameRunning = false;
        }

    }

}

bool GameEngine::getAction(std::string line, int id){

    bool actionCompleted = false;
    bool invalidAction = true;
    std::string stringCheck;

    if(line.size() >= 14) {
        // place action
        invalidAction = false;
        stringCheck = line.substr(0, 5);
        if(!(stringCheck.compare("place"))) {
            
            if(isalpha(line[6]) && isdigit(line[7])) {
                char colour = line[6];
                int shape = std::stoi(std::string(1,line[7]));
                Tile* t = players[id - 1]->getPlayerHand()->getNode(colour, shape);

                if(t != nullptr) {
                    if (isdigit(line[13])) {
                        char y = line[12];
                        int x = 0;
                        std::string cut = line.substr(13, line.size() - 13);
                        x = std::stoi(cut);
                        
                        if(board->placeTile(y, x, t, false)) {
                            if(bag->getLength() > 0) {
                                players[id - 1]->addNode(bag->pop());
                            }
                            checkScore(id, y, x);
                            actionCompleted = true;
                        }
                        else {
                            players[id - 1]->addNode(t);
                        }
                    }
                    else {
                        players[id - 1]->addNode(t);
                        errors(2);

                    }
                }
                else {
                    errors(1);
                }
            }
            else 
            {
                errors(1);
            }
        }
        else{
            invalidAction = true;
        }
        
    }

    if(line.size() == 10 && invalidAction == true) {
        // replace action
        
        invalidAction = false;
        stringCheck = line.substr(0, 7);
        if(!(stringCheck.compare("replace"))) {
            if(isalpha(line[8]) && isdigit(line[9])) {
                char colour = line[8];
                int shape = std::stoi(std::string(1,line[9]));
                if(bag->getLength() > 0) {
                    Tile* t = players[id - 1]->getPlayerHand()->getNode(colour, shape);

                    if(t != nullptr) {
                        bag->addBack(t);
                        players[id - 1]->addNode(bag->pop());
                        actionCompleted = true;
                    }
                    else {
                        errors(1);
                    }
                }
                else {
                    errors(3);
                }
            }
            else {
                errors(1);
            }
        }
        else{
            invalidAction = true;
        }
    }

    if(invalidAction == false) {
        // after replace or place commands we must now reset skip states for all players
        // as each player that skipped previously may have an option on the next turn
        for(int i = 0; i < TOTAL_PLAYERS; i++) {
            if(players[i] != nullptr) {
                players[i]->setSkip(false);
            }
        }
    }

    if(line.size() >= 4 && invalidAction == true) {
        invalidAction = false;
        stringCheck = line.substr(0, 5);
        bool spaceExists = false;

        if(!(stringCheck.compare("save "))) {
            if(line.size() > 5) {
                std::string fileName = line.substr(5, line.size() - 4);
                for(int i = 0; fileName[i]; i++) {
                    if(isspace(fileName[i])) {
                        spaceExists = true;
                    }
                }

                if(spaceExists == false) {
                    saveFile(fileName, id);
                }
                else {
                    errors(4);
                }
            }
            else {
                std::cout << "No filename given" << std::endl;
            }
        }
        else if(!(stringCheck.compare("skip"))) {
            players[id - 1]->setSkip(true);
            bool end = true;
            for(int i = 0; i < TOTAL_PLAYERS; i++) {
                if(players[i] != nullptr) {
                    if(players[i]->getSkip() == false) {
                        end = false;
                        i = TOTAL_PLAYERS;
                    }
                }
            }

            if(end) {
                gameResult();
            }

            actionCompleted = true;
        }
        else {
            invalidAction = true;
        }
    }

    if(invalidAction == true) {
        errors(2);
    }

    return actionCompleted;
}

void GameEngine::checkScore(int id, char row, int col) {
    
    char start = 'A';
    int rowCheck = 0;
    int maxRowSize = board->getVerticalSize();

    for(int i = 0; i < maxRowSize; i++) {
        if(start != row) {
            start++;
            rowCheck++;
        }
        else {
            i = maxRowSize;
        }
    }

    int tempScore = board->calculateScore();
    addScore(id, tempScore);

    if(board->checkQuirkle()) {
        std::cout << "QUIRKLE!!!" << std::endl;
    }

    if(players[id-1]->getPlayerHand()->getLength() == 0) {
        // player who uses all cards gets bonus 6 points and game ends
        addScore(id, 6);
        gameResult();
    }

}

void GameEngine::addScore(int id,int score) {
    int currScore = players[id-1]->getScore() + score;
    players[id-1]->setScore(currScore);
}

void GameEngine:: gameResult() {

    int winnerID = 1;
    bool draw = false;

    std::cout <<"\nGame over"<< std::endl;

    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        if(i + 1 != TOTAL_PLAYERS) {
            if(players[winnerID - 1]->getScore() < players[i+1]->getScore()) {
                winnerID = i + 2;
            }
            else if(players[winnerID - 1]->getScore() == players[i+1]->getScore()) {
                draw = true;
            }
        }

        std::cout << "Score for " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
    }

    if(draw == false) {
        std::cout << "Player " << players[winnerID - 1]->getName() << " won!" << std::endl;
    }
    else {
        int winningScore = players[winnerID - 1]->getScore();
        std::string winners = "";
        
        for(int i = 0; i < TOTAL_PLAYERS; i++) {
            if(players[i]->getScore() == winningScore) {
                if(winners != "") {
                    winners += " & ";
                }
                winners += players[i]->getName();
            }
        }
        std::cout << "Players " << winners << " drew!" << std::endl;
    }

    std::cout << std::endl;

    gameRunning = false;
}


void GameEngine::errors(int error) {
    if(error == 1) {
        std::cout << "Tile does not exist in your hand" << std::endl;
    }
    else if(error == 2) {
        std::cout << "Invalid Command" << std::endl;
    }
    else if(error == 3) {
        std::cout << "Bag has no more tiles" << std::endl;
    }
    else if (error == 4){
        std::cout << "Invalid filename. There should be no spaces." << std::endl;
    }

}

void GameEngine::display(int id) {
    Player* currPlayer = players[id - 1];

    std::cout << std::endl;
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

int GameEngine::getPlayerId(std::string name) {
    int playerID = 0;

    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        if(players[i] != nullptr) {
            if(!(name.compare(players[i]->getName()))) {
                playerID = players[i]->getID();
                i = TOTAL_PLAYERS;
            }
        }
    }

    return playerID;
}

void GameEngine::saveFile(std::string fileName, int id) {
    std::string directory = "saves/" + fileName;
    std::ofstream saveFile(directory, std::ofstream::out);
    std::string name;
    //saveFile.open(fileName);

    for(int i = 0; i < TOTAL_PLAYERS; i++) {
        saveFile << players[i]->getName() << std::endl;
        saveFile << players[i]->getScore() << std::endl;
        saveFile << players[i]->getPlayerHand()->savingNodes() << std::endl;

        if(players[i]->getID() == id) {
            name = players[i]->getName();
        }
    }

    saveFile << board->getVerticalSize() << "," << board->getHorizontalSize() << std::endl;
    saveFile << board->getPlaceTileOrder()->printingNodesWithCoordinates(",") << std::endl;
    saveFile << bag->savingNodes() << std::endl;
    saveFile << name;

    std::cout << "\nGame successfully saved" << std::endl;

    saveFile.close();
}