#include <iostream>
#include <string>
#include <fstream>
#include <memory>
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
    std::unique_ptr<GameEngine> engine = newEngine();
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
    // GameEngine* engine = newEngine();
    std::string input;
    bool check = false;

    while(check == false) {
        std::cout << "Enter the filename from which load a game\n" << "> ";
        std::cin >> input;
        check = loadValid(input);
    }
}

bool loadValid(std::string in) {
    bool check = false;
    std::string directory = "saves/" + in;
    
    std::ifstream file(directory);

    if(file.is_open()) {
        check = true;
        file.close();
    }
    else {
        std::cout << "File does not exist!" << std::endl; 
    }

    return check;
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

std::unique_ptr<GameEngine> newEngine() {
    std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>();
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