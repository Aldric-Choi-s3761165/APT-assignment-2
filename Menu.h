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
GameEngine* newEngine();
bool nameValid(std::string in, GameEngine& engine);
int loadValid(std::string in);
int loadPlayers(GameEngine& engine, std::string in);
int setupGame(GameEngine& engine, std::string in, int currentLine);
void corruptFile();
bool playersValid(std::string in);

int total_players;

#endif // MENU_H