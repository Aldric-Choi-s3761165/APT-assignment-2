#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

#include "Node.h"
#include "Tile.h"

class LinkedList {

public:
    LinkedList();
    ~LinkedList();
    void addNode(Tile* t);
    void addBack(Tile* t);

    // get node takes the node out of linkedlist
    Tile* getNode(Colour c, Shape s);
    Tile* pop();
    void removeAllNodes();

    void printNodes();
    int getLength();
    
private:
    Node* head;
    Node* tail;
    int length;

};

#endif // LINKEDLIST_H 