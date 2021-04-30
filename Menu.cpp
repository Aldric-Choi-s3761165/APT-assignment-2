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
        std::cin >> input;
        valid = checkValid(input);
    }

    if(input.compare("-1")) {
        
        std::cout << "\n";

        if(!input.compare("1")) {
            newGame();
    }
        else if(!input.compare("2")) {
            loadGame();
        }
    }
    else {
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

void newGame() {
    GameEngine* engine = newEngine();
    engine->setupGame();

    std::cout << "Starting a New Game \n" << std::endl;
    std::string input;

    for(int i = 1; i <= TOTAL_PLAYERS; i++) {
        std::cout << "Enter a name for player " << i << " (uppercase characters only)\n" << "> ";
        std::cin >> input;
        if(nameValid(input) == true) {
            engine->newPlayer(i, input);
        }
        else {
            i--;
        }
        
        std::cout << "\n";
    }
    std::cout << "Let's Play!" << std::endl;

    engine->gameRun(0);

    engine->testing();
}

void loadGame() {
    GameEngine* engine = newEngine();
    std::string input;
    int check = -1;
    int currentLine = 0;
    std::string directory;

    while(check == -1) {
        std::cout << "Enter the filename from which load a game\n" << "> ";
        std::cin >> input;
        check = loadValid(input);
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
        engine->gameRun(id);
    }

}

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

    return check;
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

    while(getline(file, text))
    {
        //output the text from the file
        if(playerID <= TOTAL_PLAYERS) {
            totalLineNum++;
            lineCounter++;

            if(lineCounter == 1) {
                playerName = text;
            }
            else if(lineCounter == 2) {
                //parse int
                score = std::stoi(text);
            }
            else if(lineCounter == 3) {
                
                hand = new LinkedList();
                char colour = '%';
                int shape = -1;
                bool order = false;
                bool ready = false;

                for (int i = 0; text[i]; i++) {
                    
                    if(isupper(text[i]) && isalpha(text[i]) && text[i] != ',' && order == false) {
                        colour = text[i];
                        order = true;
                    }
                    else if(isdigit(text[i]) && text[i] != ',' && order == true) {
                        shape = text[i];
                        ready = true;
                    }
                    else if(text[i] == ',' && ready == true) {
                        hand->addNode(new Tile(colour, shape));
                        order = false;
                        ready = false;
                    }
                    else if(ready == false && order == false) {
                        std::cout << text[i];
                        throw std::runtime_error("Save file corrupted or has been modified");
                    }
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
    int line = 0;
    std::string text;

    while(line < currentLine) {
        getline(file, text);
        line++;
    }

    while(getline(file, text)) {
        if(line == currentLine + 1 || line == currentLine + 2) {
            
        }
        else if(line == currentLine + 3) {

        }
        else if(line == currentLine + 4) {

        }

        line++;
    }

    file.close();
    return 0;
}

bool nameValid(std::string in) {
    bool check = true;
    int nameLength = in.length();
    for(int i = 0; i < nameLength; i++) {
        if(std::isupper(in[i]) == false || std::isalpha(in[i]) == false) {
            check = false;
            i = in.length();
        }
    }

    if(check == false) {
        std::cout << "Name is not valid!" << std::endl; 
    }

    return check;
}

GameEngine* newEngine() {
    GameEngine* engine = new GameEngine();
    return engine;
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