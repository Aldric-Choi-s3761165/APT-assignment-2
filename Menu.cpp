#include <iostream>
#include <string>
#include <fstream>
#include "Menu.h"

int main(void) {
    std::cout << "Welcome to Qurikle!" << std::endl;
    std::cout << "-------------------" << std::endl;
    menu();
    std::cout << "Goodbye" << std::endl;

    return EXIT_SUCCESS;
}

void menu() {
    
    display();

    bool valid = false;
    std::string input = "-1";
    while(valid == false) {
        std::cout << "> ";
        getline(std::cin, input);
        if(std::cin) {
            valid = checkValid(input);
        }
        else {
            valid = true;
        }
    }

    std::cout << std::endl;
    if(input.compare("-1")) {

        if(!input.compare("1")) {
            newGame();
        }
        else if(!input.compare("2")) {
            loadGame();
        }
    }
    else if(std::cin) {
        throw std::runtime_error("An error has occured");
    }

}

void display() {
    std::cout << 
        "Menu\n"
        "---- \n"
        "1. New Game \n" 
        "2. Load Game \n" 
        "3. Credits (Show student information) \n"
        "4. Quit \n" 
    << std::endl;
}

void newGame() {
    GameEngine* engine = newEngine();
    engine->setupGame();
    bool eof = false;

    std::cout << "Starting a New Game \n" << std::endl;
    std::string input;

    for(int i = 1; i <= TOTAL_PLAYERS; i++) {
        std::cout << "Enter a name for player " << i << " (uppercase characters only)\n" << "> ";
        getline(std::cin, input);

        if(std::cin) {
            if(nameValid(input, *engine) == true) {
                engine->newPlayer(i, input);
            }
            else {
                i--;
            }
            
            std::cout << "\n";
        }
        else {
            i = TOTAL_PLAYERS + 1;
            eof = true;
            std::cout << "^D\n" << std::endl;
        }
        
    }

    if(eof == false) {
        std::cout << "Let's Play!" << std::endl;
        engine->gameRun(1);
    }

    delete engine;
}

void loadGame() {
    GameEngine* engine = newEngine();
    std::string input;
    int check = -1;
    int currentLine = 0;
    std::string directory;

    while(check == -1) {
        std::cout << "Enter the filename from which load a game\n" << "> ";
        getline(std::cin, input);
        bool spaceExists = false;

        if(std::cin) {
            for(int i = 0; input[i]; i++) {
                if(isspace(input[i])) {
                    spaceExists = true;
                }
            }

            if(input == "") {
                spaceExists = true;
            }

            if(spaceExists == false) {
                check = loadValid(input);
            }
        }
        else {
            check = -2;
            std::cout << "^D\n" << std::endl;
        }
    }

    if(check == 1){
        directory = "saves/" + input;
    }
    else if(check == 2) {
        directory = input;
    }

    if(check == 1 || check == 2) {
        currentLine = loadPlayers(*engine, directory);
        int id = setupGame(*engine, directory, currentLine);
        
        if(id == 0) {
            corruptFile();
        }

        std::cout << "\nQwirkle game successfully loaded" << std::endl;
        engine->gameRun(id);
    }

    delete engine;
}

// return a new GameEngine, shared by both new and load game
GameEngine* newEngine() {
    GameEngine* engine = new GameEngine();
    return engine;
}

// check valid is to check whether the menu() input from user was a valid entry
bool checkValid(std::string in) {
    bool check = false;

    if(!in.compare("1") || !in.compare("2") || !in.compare("4")) {
        check = true;
    }
    else if(!in.compare("3")) {
        credits();
    }

    return check;
}

// check whether the input for load save was valid 'savefile' or 'directory/savefile'
int loadValid(std::string in) {
    int check = -1;
    std::string savesDirectory = "saves/" + in;
    
    // if they provide an input of just the save name 
    // (located in saves file when a game is saved)

    std::ifstream savesDirectoryFile(savesDirectory);

    // if they provide an input of a file + directory of their choice on 
    // desktop as they may have moved the save location elsewhere

    std::ifstream chosenDirectoryFile(in);

    if(savesDirectoryFile.is_open()) {
        check = 1;
        savesDirectoryFile.close();
    }
    else if(chosenDirectoryFile.is_open()) {
        check = 2;
        chosenDirectoryFile.close();
    }
    else {
        std::cout << "File does not exist!" << std::endl; 
    }

    // if return 1 or 2 a file is valid otherwise send -1
    return check;
}

void corruptFile() {
    throw std::runtime_error("Save file corrupted or has been modified");
}

int loadPlayers(GameEngine& engine, std::string in) {
    std::string text;
    int playerID = 1;
    std::string playerName = "";
    LinkedList* hand;
    int score = 0;

    int lineCounter = 0;
    int totalLineNum = 0;
    std::ifstream file(in);

    // loop each line until we finish with all players in the save file
    while(getline(file, text))
    {
        // loop until we finish with all players
        // each save file contains 3 lines worth of player information
        if(playerID <= TOTAL_PLAYERS) {
            totalLineNum++;
            lineCounter++;

            // line 1 of each player loop contains the player name
            // check whether name is valid then set it
            if(lineCounter == 1) {
                playerName = "";
                for(int i = 0; text[i] && int(text[i]) != ASCII_CARRIAGE; i++) {
                    playerName = playerName + text[i];
                    // std::cout << int(text[i]) << std::endl;
                }

                if(nameValid(playerName, engine) == false) {
                    corruptFile();
                }

            }

            // line 2 of each player loop contains the score
            // player can modify this line for all characters greater than position 1 (index 0)
            // as the check, checks char of line[0] whether it is digit and sets score to it
            else if(lineCounter == 2) {
                //parse int

                for(int i = 0; text[i] && int(text[i]) != ASCII_CARRIAGE; i++) {
                    if(!(isdigit(text[i]))) {
                        corruptFile();
                    }
                }
                
                score = std::stoi(text);
            }

            else if(lineCounter == 3) {
                
                hand = new LinkedList();
                char colour = '%';
                int shape = -1;
                bool order = false;
                bool ready = false;
                int counter = 0;

                for (int i = 0; text[i]; i++) {
                    
                    if(isupper(text[i]) && isalpha(text[i]) && text[i] != ',' && order == false) {
                        colour = text[i];
                        order = true;
                    }
                    else if(isdigit(text[i]) && text[i] != ',' && order == true) {
                        shape = std::stoi(std::string(1,text[i]));
                        ready = true;
                    }
                    else if(text[i] == ',' && ready == true) {
                        hand->addNode(new Tile(colour, shape));
                        order = false;
                        ready = false;
                    }
                    else if(ready == false && order == false) {
                        corruptFile();
                    }
                    counter = i;
                }
                if(text[counter+1] == false && ready == true) {
                    hand->addNode(new Tile(colour, shape));
                }

                engine.existingPlayer(playerID, playerName, score, hand);
                
                playerID++;
                lineCounter = 0;
            }
        }
    }
    
    file.close();

    return totalLineNum;
}

int setupGame(GameEngine& engine, std::string in, int currentLine) {
    std::ifstream file(in);
    int line = 1;
    std::string text;
    LinkedList* bag = new LinkedList();
    int beginningPlayerID = 0;

    // loop the file till we get to the line 
    // we finished at previously with loadPlayers()
    while(line <= currentLine) {
        getline(file, text);
        line++;
    }

    while(getline(file, text)) {
        if(line == currentLine + 1) {            
            
            std::string rowCheck = "";
            std::string colCheck = "";
            bool commaCheck = false;

            for(int i = 0; text[i] && int(text[i]) != ASCII_CARRIAGE ; i++) {
                if(commaCheck == false) {
                    if(isdigit(text[i])) {
                        rowCheck = rowCheck + text[i];
                    }
                    else if(text[i] == ',') {
                        commaCheck = true;
                    }
                    else {
                        corruptFile();
                    }
                }
                else {
                    if(isdigit(text[i])) {
                        colCheck = colCheck + text[i];
                    }
                    else {
                        corruptFile();
                    }
                }
            }

            int row = std::stoi(rowCheck);
            int col = std::stoi(colCheck);
            getline(file, text);

            if(file.eof() || row > MAX_BOARD_DIMENSION || col > MAX_BOARD_DIMENSION) {
                corruptFile();
            }

            engine.createBoard(row, col, text);

            // account for line 2 since we getline again
            line++;
        }
        else if(line == currentLine + 3) {
            char colour = '%';
            int shape = -1;
            bool order = false;
            bool ready = false;
            int counter = 0;

            for (int i = 0; text[i]; i++) {
                
                if(isupper(text[i]) && isalpha(text[i]) && text[i] != ',' && order == false) {
                    colour = text[i];
                    order = true;
                }
                else if(isdigit(text[i]) && text[i] != ',' && order == true) {
                    shape = std::stoi(std::string(1,text[i]));
                    ready = true;
                }
                else if(text[i] == ',' && ready == true) {
                    bag->addNode(new Tile(colour, shape));
                    order = false;
                    ready = false;
                }
                else if(ready == false && order == false) {
                    corruptFile();
                }
                
                counter = i;  
            }
            
            if(text[counter+1] == false && ready == true) {
                bag->addNode(new Tile(colour, shape));
            }

            engine.newBag(bag);
            
        }
        else if(line == currentLine + 4) {
            std::string playerName = text;
            beginningPlayerID = engine.getPlayerId(playerName);
        }
        else {
            corruptFile();
        }

        line++;
    }

    file.close();
    return beginningPlayerID;
}

// check whether the given name is valid for both new game and load game
// for load game it checks whether the name was altered
bool nameValid(std::string in, GameEngine& engine) {
    bool check = true;
    int nameLength = in.length();

    for(int i = 0; i < nameLength; i++) {
        if(std::isupper(in[i]) == false || std::isalpha(in[i]) == false) {
            check = false;
            i = in.length();
        }
    }

    if(nameLength == 0) {
        check = false;
    }

    if(check == false) {
        std::cout << "Name is not valid!" << std::endl; 
    }

    if(check == true) {
        if(engine.getPlayerId(in) != 0){
            std::cout << "There is already an existing name." << std::endl;
            check = false;
        }
    }

    return check;
}

void credits() {
    std::string arr[TOTAL_STUDENTS][3] = {
        {"Joshua Besei", "s3839264", "s3839264@student.rmit.edu.au"},
        {"Jacqueline Ann Co Lim", "s3753072", "s3753072@student.rmit.edu.au"},
        {"Aldric Choi", "s3761165", "s3761165@student.rmit.edu.au"},
        {"Pham Nguyen Ngoc Kinh", "s3773604", "s3773604@student.rmit.edu.au"},
    };

    std::cout << "----------------------------------\n";
    for(int i = 0; i < TOTAL_STUDENTS; i++) {
        std::cout <<
        "Name: <" + arr[i][0] +
        ">\nStudent ID: <" + arr[i][1] +
        ">\nEmail: <" + arr[i][2] +
        ">\n";
        if(i + 1 != TOTAL_STUDENTS) {
            std::cout << "\n";
        }
    }
    std::cout << "----------------------------------\n";
    display();

}