#ifndef MENU_H
#define MENU_H 

#include "GameEngine.h"
#include "Types.h"
    
void menu();
void newGame();
void loadGame();
void credits();
bool checkValid(std::string in);
void display();
std::unique_ptr<GameEngine> newEngine();
bool nameValid(std::string in);
bool loadValid(std::string in);

#endif // MENU_H