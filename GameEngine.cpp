#include "GameEngine.h"
#include <iostream>
#include <random>
#include <cstring>
#include <fstream>

int movesMade = 0;

GameEngine::GameEngine() {
    bag = new LinkedList();
    board = new Board();
    gameRunning = true;
}

GameEngine::~GameEngine() {
    delete bag;
    delete board;
        
    for(Player* player : players){
        delete player;
    }
}

// precondition; id is valid above 0 and hasn't already been added
// hence if we add player of id 1 and we create a second new player of
// id 1 again, this will replace the first created player
// However, the bag state will decrease further and the tiles that the
// first player held will be lost

bool GameEngine::newPlayer(int id, std::string n) {
    players.push_back(new Player(id, n));

    for(int i = 0; i < PLAYER_HAND_LIMIT; i++) {
        Tile* t = bag->pop();
        if(t != nullptr) {
            players.at(id-1)->addNode(t);
        }
        else {
            throw std::runtime_error("Bag is empty, error has occured"); //temp testing may remove later
        }
    }

    return true;
}

bool GameEngine::existingPlayer(int id, std::string name, int score, LinkedList* hand) {
    players.push_back(new Player(id, name, score, hand));
        
    return true;
}

void GameEngine::createBoard(int row, int col, std::string states) {
    board->setBoard(row, col);
    // setup states
    Colour colour = '%';
    Shape shape = -1;
    char boardRow = '%';
    std::string boardColStr;
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
            boardColStr += std::string(1,states[i]);
            ready = true;
        }
        else if(states[i] == ',' && ready == true && order == 4) {
            boardCol = std::stoi(boardColStr);
            order = 0;
            ready = false;
            Tile* t = new Tile(colour, shape);
            t->setRowCol(rowCheck, boardCol);
            loadTiles[loadTilesCounter] = t;
            loadTilesCounter++;
            boardColStr = "";
        }
        else if(ready == false && order != 0) {
            throw std::runtime_error("Load game board states have been modified");
        }

        counter = i;
    }

    if(ready == true) {
        Tile* t = new Tile(colour, shape);
        boardCol = std::stoi(boardColStr);
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
                if(row >= 0 && row < board->getVerticalSize() && col >= 0 && col < board->getHorizontalSize()) {
                    tilePlaced = board->placeTile(loadTiles[i]->getCharColour(row), loadTiles[i]->getCol(), loadTiles[i], true);
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
                if(id > players.size()) {
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
                Tile* t = players.at(id-1)->getPlayerHand()->getNode(colour, shape);

                if(t != nullptr) {
                    std::string cut = line.substr(13, line.size() - 13);
                    bool incorrect = false;
                    for(int i = 0; cut[i]; i++) {
                        if(!(isdigit(cut[i]))) {
                            incorrect = true;
                        }
                    }

                    if (isalpha(line[12]) && incorrect == false) {
                        char y = line[12];
                        int x = 0;
                        x = std::stoi(cut);
                        
                        if(board->placeTile(y, x, t, false)) {
                            movesMade++;                            
                            checkScore(id, y, x);
                        }
                        else {
                            players.at(id-1)->addNode(t);
                        }
                    }
                    else {
                        players.at(id-1)->addNode(t);
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
                if(movesMade > 0){
                    std::cout << "Cannot replace a tile in the middle of your turn." << std::endl;
                }
                else{
                    if(bag->getLength() > 0) {
                        Tile* t = players.at(id-1)->getPlayerHand()->getNode(colour, shape);

                        if(t != nullptr) {
                            bag->addBack(t);
                            players.at(id-1)->addNode(bag->pop());
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
            }
            else {
                errors(1);
            }
        }
        else{
            invalidAction = true;
        }
    }

    if(line.size() == 4){
        stringCheck = line.substr(0, 4);
        if(!(stringCheck.compare("help"))) {
            std::cout << "\n- These are the commands you can use:" << std::endl;
            std::cout << "??? Note 1: There should be no extra spaces in the commands."<< std::endl;
            std::cout << "??? Note 2: The board resizes when you put it on the edge" << std::endl;
            std::cout << "??? To place a tile: Type 'place <Tile> at <Position on Board>' e.g. place G5 at A3" << std::endl;
            std::cout << "??? To replace a tile you dont want in your hand: Type 'replace <Tile>' e.g. replace C3" << std::endl;
            std::cout << "??? You can place multiple tiles in a turn, just type 'done' to check if you have placed all placeable tiles" << std::endl;
            std::cout << "??? If you do not have any valid tiles to place in your hand: Type 'skip'" << std::endl;
            std::cout << "??? To save the game: Type 'save' then filname e.g. 'save filename'" << std::endl;
            std::cout << "??? To end the game without saving: type 'ctrl+d'\n"<< std::endl;

            std::cout << "\n- Game Rules:" << std::endl;
            std::cout << "??? There can only be 6 tiles per row or column of tiles" << std::endl;
            std::cout << "??? You can put the same colour in the same row but not on the same column" << std::endl;
            std::cout << "??? You can put the same shape in the same column but not on the same row" << std::endl;
            
            invalidAction = false;
        }
    }

    if(invalidAction == false) {
        // after replace or place commands we must now reset skip states for all players
        // as each player that skipped previously may have an option on the next turn
        for(int i = 0; i < players.size(); i++) {
            if(players.at(i) != nullptr) {
                players.at(i)->setSkip(false);
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
                if(movesMade > 0){
                    std::cout << "Cannot save file while in the middle of your turn." << std::endl;
                }
                else{
                    if(spaceExists == false) {
                        saveFile(fileName, id);
                    }
                    else {
                        errors(4);
                    }
                }                
            }
            else {
                std::cout << "No filename given" << std::endl;
            }
        }
        else if(!(stringCheck.compare("skip"))) {
            if(movesMade > 0){
                std::cout << "Cannot skip while in the middle of your turn." << std::endl;
            }
            else{
                players.at(id-1)->setSkip(true);
                bool end = true;
                for(int i = 0; i < players.size(); i++) {
                    if(players.at(i) != nullptr) {
                        if(players.at(i)->getSkip() == false) {
                            end = false;
                            i = players.size();
                        }
                    }
                }

                if(end) {
                    gameResult();
                }

                actionCompleted = true;
            }
            
        }
        else if(!(stringCheck.compare("done"))) {
            if(movesMade > 0){
                for(int i = 0; i < movesMade; i++){
                    if(bag->getLength() > 0) {
                        players.at(id-1)->addNode(bag->pop());
                    }
                }
                movesMade = 0;
                actionCompleted = true;
            }
            else{
                std::cout << "Invalid command. You did not make a valid move." << std::endl;
            }
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

    if(players.at(id-1)->getPlayerHand()->getLength() == 0) {
        // player who uses all cards gets bonus 6 points and game ends
        addScore(id, 6);
        gameResult();
    }

}

void GameEngine::addScore(int id,int score) {
    int currScore = players.at(id-1)->getScore() + score;
    players.at(id-1)->setScore(currScore);
}

void GameEngine:: gameResult() {

    std::cout << std::endl;
    board->printBoard();

    int winnerID = 1;
    bool draw = false;

    std::cout <<"\nGame over"<< std::endl;

    for(int i = 0; i < players.size(); i++) {
        if(i + 1 != players.size()) {
            if(players.at(winnerID - 1)->getScore() < players.at(i+1)->getScore()) {
                winnerID = i + 2;
            }
            else if(players.at(winnerID - 1)->getScore() == players.at(i+1)->getScore()) {
                draw = true;
            }
        }

        std::cout << "Score for " << players.at(i)->getName() << ": " << players.at(i)->getScore() << std::endl;
    }

    if(draw == false) {
        std::cout << "Player " << players.at(winnerID - 1)->getName() << " won!" << std::endl;
    }
    else {
        int winningScore = players.at(winnerID - 1)->getScore();
        std::string winners = "";
        
        for(int i = 0; i < players.size(); i++) {
            if(players.at(i)->getScore() == winningScore) {
                if(winners != "") {
                    winners += " & ";
                }
                winners += players.at(i)->getName();
            }
        }
        std::cout << "Players " << winners << " drew!" << std::endl;
    }

    std::cout << std::endl;

    gameRunning = false;
}


void GameEngine::errors(int error) {
    if(error == 1) {
        std::cout << "INVALID: Tile does not exist in your hand or command typed incorrectly\nMake sure your command contains no extra spaces" << std::endl;
    }
    else if(error == 2) {
        std::cout << "INVALID: Invalid Command" << std::endl;
    }
    else if(error == 3) {
        std::cout << "INVALID: Bag has no more tiles" << std::endl;
    }
    else if (error == 4){
        std::cout << "INVALID: Invalid filename. There should be no spaces." << std::endl;
    }

}

void GameEngine::display(int id) {
    Player* currPlayer = players.at(id - 1);

    std::cout << std::endl;
    std::cout << "If you are unsure of the commands or gameplay, please type 'help'" << std::endl;
    std::cout << currPlayer->getName() << ", it's your turn" << std::endl;
    for(int i = 0; i < players.size(); i++) {
        Player* player = players.at(i);
        std::cout << "Score for " << player->getName() << ": " << players.at(i)->getScore() << std::endl;
    }

    board->printBoard();

    std::cout << std::endl;
    if(movesMade > 0){
        std::cout << "You can place another tile. \nPlease enter 'done' if you are done placing all tiles." << std::endl;
    }
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

    for(int i = 0; i < players.size(); i++) {
        if(players.at(i) != nullptr) {
            if(!(name.compare(players.at(i)->getName()))) {
                playerID = players.at(i)->getID();
                i = players.size();
            }
        }
    }

    return playerID;
}

void GameEngine::saveFile(std::string fileName, int id) {
    std::string directory = "saves/" + fileName;
    std::ofstream saveFile(directory, std::ofstream::out);
    std::string name;

    saveFile << players.size() << std::endl;

    for(int i = 0; i < players.size(); i++) {
        saveFile << players.at(i)->getName() << std::endl;
        saveFile << players.at(i)->getScore() << std::endl;
        saveFile << players.at(i)->getPlayerHand()->savingNodes() << std::endl;

        if(players.at(i)->getID() == id) {
            name = players.at(i)->getName();
        }
    }

    saveFile << board->getVerticalSize() << "," << board->getHorizontalSize() << std::endl;
    LinkedList* tiles = board->getAllTiles();
    saveFile << tiles->printingNodesWithCoordinates(",") << std::endl;
    saveFile << bag->savingNodes() << std::endl;
    saveFile << name;

    delete tiles;

    std::cout << "\nGame successfully saved" << std::endl;

    saveFile.close();
}