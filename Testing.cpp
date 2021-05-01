#include <iostream>
#include "GameEngine.h"
#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
#include "Types.h"

void testLinkedList(LinkedList& l);
void testPlayers(Player& p);
void testEngine(GameEngine& e);
void testBoard(Board& b);

int main(void) {

    // test one at a time then increase the tests to see if they all work together correctly
    LinkedList* l = new LinkedList();
    //Player* p = new Player(0, "J");
    //GameEngine* e = new GameEngine();
    //Board* b = new Board();

    // test one at a time
    testLinkedList(*l);
    //testPlayers(*p);
    //testEngine(*e);
    //testBoard(*b);


    // add these to test if deconstructors are the cause for segmentation fault
    
    delete l;
    //delete p;
    //delete e;
    //delete b;
    

    return EXIT_SUCCESS;
}

void testLinkedList(LinkedList& l) {
    // l.addNode(new Tile(RED, CIRCLE));
    // l.addNode(new Tile(YELLOW, SQUARE));
    l.addNode(new Tile(GREEN, DIAMOND));
    l.addNode(new Tile(BLUE, STAR_6));

    l.addBack(new Tile(RED, CIRCLE));
    l.addBack(new Tile(YELLOW, SQUARE));
    l.addBack(new Tile(GREEN, DIAMOND));
    l.addBack(new Tile(BLUE, STAR_6));

    //std::cout << l.getLength() << std::endl;
    //std::cout << l.pop()->getColour() << l.pop()->getShape() << std::endl;
    l.printNodes();
    l.removeAllNodes();
}

void testPlayers(Player& p) {
    p.addNode(new Tile(RED, CIRCLE));
    p.addNode(new Tile(YELLOW, SQUARE));
    p.addNode(new Tile(GREEN, DIAMOND));
    p.addNode(new Tile(BLUE, STAR_6));

    p.displayTileHand();
    p.getPlayerHand()->printNodes();
}

void testEngine(GameEngine& e) {
    // only add two players, may need to account for addition of > 2 since may cause error
    e.setupGame();

    e.newPlayer(1, "J");
    e.newPlayer(2, "B");

    e.gameRun(0);
    e.testing();
}

void testBoard(Board& b) {
    b.printBoard();
    b.placeTile(2, 2, new Tile(RED, CIRCLE));
    b.printBoard();
    b.placeTile(0, 1, new Tile(YELLOW, SQUARE));
    b.printBoard();
    b.placeTile(5, 3, new Tile(GREEN, DIAMOND));
    b.printBoard();
    b.placeTile(4, 4, new Tile(BLUE, STAR_6));
    b.printBoard();

    std::cout << b.getHorizontalSize() << b.getVerticalSize() << std::endl;
}